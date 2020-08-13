require "scripts.core.ability"
require "scripts.core.projectile"
require "gamemode.hookwars.modifiers.modifier_hooked";
require "gamemode.hookwars.modifiers.modifier_hooking";

-- hook ability
Hook = class(Ability)

local Z_OFFSET = 3

function Hook:OnCreated ()
	self:RegisterVariable("max_range", 500)
	self:RegisterVariable("cast_time", 0.1)
	self:RegisterVariable("cast_point", 0.0)
	self:RegisterVariable("range", self:GetSpecialValue("range"))
	self:RegisterVariable("speed", self:GetSpecialValue("speed"))
	self:RegisterVariable("damage", self:GetSpecialValue("damage"))

	self:SetCastingBehavior(CastingBehavior(CastingBehavior.POINT_TARGET));

	self.OnTick = self.OnTick
	self:SetLevel(1)
end

function Hook:OnSpellStart ()
	AudioRequestBus.Broadcast.PlaySound("Play_sfx_hook_throw");
	Debug.Log('Firing hook!')
	self.finished = false

	local target = self:GetCursorPosition()
	local caster = self:GetCaster()
	local origin = self:GetCaster():GetPosition()
	self.isReturning = false

	Debug.Log('Origin of hook is ' .. tostring(origin) .. ' : ' .. tostring(self:GetCaster():GetId()) .. caster:GetName())
	Debug.Log('Destination is ' .. tostring(target))

	local direction = (target - origin)
	direction.z = 0
	origin.z = origin.z + Z_OFFSET
	direction = direction:GetNormalized()
	Debug.Log('Direction is ' .. tostring(direction))
	local destination = origin + (direction * self:GetValue("range"))
	Debug.Log('Final travel point is ' .. tostring(target))

	self.projectile = Projectile({
		startingPosition = origin,
		targetPosition = destination,
		speed = self:GetValue("speed"),
		particle = "hookwars.fire_ball",
		triggerRadius = 1
	});

	self.hookingModifier = caster:AddNewModifier(caster, self, "modifier_hooking", {})

	self.unlisten = self.projectile:OnEntityEnter(function (entityId)
		if entityId == self:GetCaster():GetId() then
			return
		end
		self.attachedUnit = Unit({ entityId = entityId})
		AudioRequestBus.Broadcast.PlaySound("Play_sfx_hook_hit");
		local damage = Damage();
		damage.type = Damage.DAMAGE_TYPE_PHYSICAL;
		damage.damage = self:GetValue("damage");
		self.attachedUnit:ApplyDamage(damage)
		if self.attachedUnit:FindModifierByTypeId("modifier_hooked") then
			self.attachedUnit:Kill()
			self.attachedUnit = nil
		elseif not self.attachedUnit:IsAlive() then
			self.attachedUnit = nil
		else
			self.hookedModifier = self.attachedUnit:AddNewModifier(caster, self, "modifier_hooked", {})
		end

		caster:SetValue("experience", caster:GetValue("experience") + 1)

		if not self.tickHandler then
			self.tickHandler = TickBus.Connect(self)
		end
		self:Return()
	end)

	self.projectile:OnProjectileHit(function ()
		-- hit the end position without hitting any heroes
		self:Return()
	end)

	self.projectile:Fire()
end

function Hook:OnTick ()

	local origin = self.projectile:GetPosition()
	origin.z = origin.z - Z_OFFSET

	if self.finished or not self.attachedUnit or not self.attachedUnit:IsAlive() then
		self.tickHandler:Disconnect()
		self.tickHandler = nil
		self.attachedUnit = nil
		self.hookedModifier = nil

		self.attachedUnit:SetPosition(origin,true)
		return
	end

	self.attachedUnit:SetPosition(origin,2)
end

function Hook:Return ()
	self.unlisten()
	if self.hookingModifier then
		self.hookingModifier:Destroy()
		self.hookingModifier = nil
	end

	local origin = self:GetCaster():GetPosition()
	local currentLocation = self.projectile:GetPosition()
	local direction = currentLocation - origin
	direction.z = 0
	direction = direction:GetNormalized()

	origin = origin + direction
	origin.z = origin.z + Z_OFFSET
	Debug.Log('Returning projectile to ' .. tostring(origin) .. ' : ' .. tostring(self:GetCaster():GetId()))
	if not self.isReturning then
		self.isReturning = true
		self.projectile:Fire({
			targetPosition = origin,
		})
	else
		Debug.Log('Releasing!')
		self.finished = true
		self.projectile:Release()
		self.projectile = nil
		self.attachedUnit = nil
		if self.hookedModifier then
			self.hookedModifier:Destroy()
			self.hookedModifier = nil
		end
		if self.tickHandler then
			self.tickHandler:Disconnect()
			self.tickHandler = nil
		end
	end
end

return Hook