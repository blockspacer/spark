require "scripts.core.ability"
require "gamemode.Spark.modifiers.modifier_double_damage";

local double_damage_rune = class(Ability)


function double_damage_rune:OnCreated ()
	self:RegisterVariable("max_range", 0.5)
	self:RegisterVariable("cast_time", 0.1)
	self:RegisterVariable("cast_point", 0.0)

	self:SetCastingBehavior(CastingBehavior(CastingBehavior.UNIT_TARGET));
	self:SetLevel(1)
end

function double_damage_rune:OnSpellStart ()    
	self.hasteModifier = self:GetCaster():AddNewModifier(self:GetCaster(), self, "modifier_double_damage", {duration = self:GetSpecialValue("double_damage_duration")})

	GameManagerRequestBus.Broadcast.DestroyEntity(GetId(self:GetCursorTarget()))
	self:DetachAndDestroy();
end

return double_damage_rune
