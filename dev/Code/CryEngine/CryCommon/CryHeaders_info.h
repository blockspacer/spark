/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/
// Original file Copyright Crytek GMBH or its affiliates, used under license.

#ifndef CRYINCLUDE_CRYCOMMON_CRYHEADERS_INFO_H
#define CRYINCLUDE_CRYCOMMON_CRYHEADERS_INFO_H
#pragma once

#include "CryHeaders.h"

STRUCT_INFO_BEGIN(CryVertex)
STRUCT_VAR_INFO(p, TYPE_INFO(Vec3))
STRUCT_VAR_INFO(n, TYPE_INFO(Vec3))
STRUCT_INFO_END(CryVertex)

STRUCT_INFO_BEGIN(CryFace)
STRUCT_VAR_INFO(v0, TYPE_INFO(int))
STRUCT_VAR_INFO(v1, TYPE_INFO(int))
STRUCT_VAR_INFO(v2, TYPE_INFO(int))
STRUCT_VAR_INFO(MatID, TYPE_INFO(int))
STRUCT_INFO_END(CryFace)

STRUCT_INFO_BEGIN(CryUV)
STRUCT_VAR_INFO(u, TYPE_INFO(float))
STRUCT_VAR_INFO(v, TYPE_INFO(float))
STRUCT_INFO_END(CryUV)

STRUCT_INFO_BEGIN(CrySkinVtx)
STRUCT_VAR_INFO(bVolumetric, TYPE_INFO(int))
STRUCT_VAR_INFO(idx, TYPE_INFO_ARRAY(4, TYPE_INFO(int)))
STRUCT_VAR_INFO(w, TYPE_INFO_ARRAY(4, TYPE_INFO(float)))
STRUCT_VAR_INFO(M, TYPE_INFO(Matrix33))
STRUCT_INFO_END(CrySkinVtx)

STRUCT_INFO_BEGIN(CryLink)
STRUCT_VAR_INFO(BoneID, TYPE_INFO(int))
STRUCT_VAR_INFO(offset, TYPE_INFO(Vec3))
STRUCT_VAR_INFO(Blending, TYPE_INFO(float))
STRUCT_INFO_END(CryLink)

STRUCT_INFO_BEGIN(CryIRGB)
STRUCT_VAR_INFO(r, TYPE_INFO(unsigned char))
STRUCT_VAR_INFO(g, TYPE_INFO(unsigned char))
STRUCT_VAR_INFO(b, TYPE_INFO(unsigned char))
STRUCT_INFO_END(CryIRGB)

STRUCT_INFO_BEGIN(CryBonePhysics_Comp)
STRUCT_VAR_INFO(nPhysGeom, TYPE_INFO(int))
STRUCT_VAR_INFO(flags, TYPE_INFO(int))
STRUCT_VAR_INFO(min, TYPE_ARRAY(3, TYPE_INFO(float)))
STRUCT_VAR_INFO(max, TYPE_ARRAY(3, TYPE_INFO(float)))
STRUCT_VAR_INFO(spring_angle, TYPE_ARRAY(3, TYPE_INFO(float)))
STRUCT_VAR_INFO(spring_tension, TYPE_ARRAY(3, TYPE_INFO(float)))
STRUCT_VAR_INFO(damping, TYPE_ARRAY(3, TYPE_INFO(float)))
STRUCT_VAR_INFO(framemtx, TYPE_ARRAY(3, TYPE_ARRAY(3, TYPE_INFO(float))))
STRUCT_INFO_END(CryBonePhysics_Comp)

STRUCT_INFO_BEGIN(CryBoneDescData_Comp)
STRUCT_VAR_INFO(m_nControllerID, TYPE_INFO(unsigned int))
STRUCT_VAR_INFO(m_PhysInfo, TYPE_ARRAY(2, TYPE_INFO(BONE_PHYSICS_COMP)))
STRUCT_VAR_INFO(m_fMass, TYPE_INFO(float))
STRUCT_VAR_INFO(m_DefaultW2B, TYPE_INFO(Matrix34))
STRUCT_VAR_INFO(m_DefaultB2W, TYPE_INFO(Matrix34))
STRUCT_VAR_INFO(m_arrBoneName, TYPE_ARRAY(256, TYPE_INFO(char)))
STRUCT_VAR_INFO(m_nLimbId, TYPE_INFO(int))
STRUCT_VAR_INFO(m_nOffsetParent, TYPE_INFO(int))
STRUCT_VAR_INFO(m_numChildren, TYPE_INFO(unsigned int))
STRUCT_VAR_INFO(m_nOffsetChildren, TYPE_INFO(int))
STRUCT_INFO_END(CryBoneDescData_Comp)

STRUCT_INFO_BEGIN(BONE_ENTITY)
STRUCT_VAR_INFO(BoneID, TYPE_INFO(int))
STRUCT_VAR_INFO(ParentID, TYPE_INFO(int))
STRUCT_VAR_INFO(nChildren, TYPE_INFO(int))
STRUCT_VAR_INFO(ControllerID, TYPE_INFO(unsigned int))
STRUCT_VAR_INFO(prop, TYPE_ARRAY(32, TYPE_INFO(char)))
STRUCT_VAR_INFO(phys, TYPE_INFO(BONE_PHYSICS_COMP))
STRUCT_INFO_END(BONE_ENTITY)

ENUM_INFO_BEGIN(ChunkTypes)
ENUM_ELEM_INFO(, ChunkType_ANY)
ENUM_ELEM_INFO(, ChunkType_Mesh)
ENUM_ELEM_INFO(, ChunkType_Helper)
ENUM_ELEM_INFO(, ChunkType_VertAnim)
ENUM_ELEM_INFO(, ChunkType_BoneAnim)
ENUM_ELEM_INFO(, ChunkType_GeomNameList)
ENUM_ELEM_INFO(, ChunkType_BoneNameList)
ENUM_ELEM_INFO(, ChunkType_MtlList)
ENUM_ELEM_INFO(, ChunkType_MRM)
ENUM_ELEM_INFO(, ChunkType_SceneProps)
ENUM_ELEM_INFO(, ChunkType_Light)
ENUM_ELEM_INFO(, ChunkType_PatchMesh)
ENUM_ELEM_INFO(, ChunkType_Node)
ENUM_ELEM_INFO(, ChunkType_Mtl)
ENUM_ELEM_INFO(, ChunkType_Controller)
ENUM_ELEM_INFO(, ChunkType_Timing)
ENUM_ELEM_INFO(, ChunkType_BoneMesh)
ENUM_ELEM_INFO(, ChunkType_BoneLightBinding)
ENUM_ELEM_INFO(, ChunkType_MeshMorphTarget)
ENUM_ELEM_INFO(, ChunkType_BoneInitialPos)
ENUM_ELEM_INFO(, ChunkType_SourceInfo)
ENUM_ELEM_INFO(, ChunkType_MtlName)
ENUM_ELEM_INFO(, ChunkType_ExportFlags)
ENUM_ELEM_INFO(, ChunkType_DataStream)
ENUM_ELEM_INFO(, ChunkType_MeshSubsets)
ENUM_ELEM_INFO(, ChunkType_MeshPhysicsData)
ENUM_ELEM_INFO(, ChunkType_CompiledBones)
ENUM_ELEM_INFO(, ChunkType_CompiledPhysicalBones)
ENUM_ELEM_INFO(, ChunkType_CompiledMorphTargets)
ENUM_ELEM_INFO(, ChunkType_CompiledPhysicalProxies)
ENUM_ELEM_INFO(, ChunkType_CompiledIntFaces)
ENUM_ELEM_INFO(, ChunkType_CompiledIntSkinVertices)
ENUM_ELEM_INFO(, ChunkType_CompiledExt2IntMap)
ENUM_ELEM_INFO(, ChunkType_BreakablePhysics)
ENUM_ELEM_INFO(, ChunkType_FaceMap)
ENUM_ELEM_INFO(, ChunkType_MotionParameters)
ENUM_ELEM_INFO(, ChunkType_FootPlantInfo)
ENUM_ELEM_INFO(, ChunkType_BonesBoxes)
ENUM_ELEM_INFO(, ChunkType_FoliageInfo)
ENUM_INFO_END(ChunkTypes)

STRUCT_INFO_BEGIN(RANGE_ENTITY)
STRUCT_VAR_INFO(name, TYPE_ARRAY(32, TYPE_INFO(char)))
STRUCT_VAR_INFO(start, TYPE_INFO(int))
STRUCT_VAR_INFO(end, TYPE_INFO(int))
STRUCT_INFO_END(RANGE_ENTITY)

STRUCT_INFO_BEGIN(TIMING_CHUNK_DESC_0918)
STRUCT_VAR_INFO(m_SecsPerTick, TYPE_INFO(float))
STRUCT_VAR_INFO(m_TicksPerFrame, TYPE_INFO(int))
STRUCT_VAR_INFO(global_range, TYPE_INFO(RANGE_ENTITY))
STRUCT_VAR_INFO(qqqqnSubRanges, TYPE_INFO(int))
STRUCT_INFO_END(TIMING_CHUNK_DESC_0918)


STRUCT_INFO_BEGIN(SPEED_CHUNK_DESC_2)
STRUCT_VAR_INFO(Speed, TYPE_INFO(float))
STRUCT_VAR_INFO(Distance, TYPE_INFO(float))
STRUCT_VAR_INFO(Slope, TYPE_INFO(float))
STRUCT_VAR_INFO(AnimFlags, TYPE_INFO(int))
STRUCT_VAR_INFO(MoveDir, TYPE_ARRAY(3, TYPE_INFO(f32)))
STRUCT_VAR_INFO(StartPosition, TYPE_INFO(QuatT))
STRUCT_INFO_END(SPEED_CHUNK_DESC_2)

STRUCT_INFO_BEGIN(MTL_NAME_CHUNK_DESC_0800)
STRUCT_VAR_INFO(nFlags, TYPE_INFO(int))
STRUCT_VAR_INFO(nFlags2, TYPE_INFO(int))
STRUCT_VAR_INFO(name, TYPE_ARRAY(128, TYPE_INFO(char)))
STRUCT_VAR_INFO(nPhysicalizeType, TYPE_INFO(int))
STRUCT_VAR_INFO(nSubMaterials, TYPE_INFO(int))
STRUCT_VAR_INFO(nSubMatChunkId, TYPE_ARRAY(MTL_NAME_CHUNK_DESC_0800_MAX_SUB_MATERIALS, TYPE_INFO(int)))
STRUCT_VAR_INFO(nAdvancedDataChunkId, TYPE_INFO(int))
STRUCT_VAR_INFO(sh_opacity, TYPE_INFO(float))
STRUCT_VAR_INFO(reserve, TYPE_ARRAY(32, TYPE_INFO(int)))
STRUCT_INFO_END(MTL_NAME_CHUNK_DESC_0800)

STRUCT_INFO_BEGIN(MTL_NAME_CHUNK_DESC_0802)
STRUCT_VAR_INFO(name, TYPE_ARRAY(128, TYPE_INFO(char)))
STRUCT_VAR_INFO(nSubMaterials, TYPE_INFO(int))
STRUCT_INFO_END(MTL_NAME_CHUNK_DESC_0802)

STRUCT_INFO_BEGIN(MESH_CHUNK_DESC_0745)
STRUCT_VAR_INFO(flags1, TYPE_INFO(unsigned char))
STRUCT_VAR_INFO(flags2, TYPE_INFO(unsigned char))
STRUCT_VAR_INFO(nVerts, TYPE_INFO(int))
STRUCT_VAR_INFO(nTVerts, TYPE_INFO(int))
STRUCT_VAR_INFO(nFaces, TYPE_INFO(int))
STRUCT_VAR_INFO(VertAnimID, TYPE_INFO(int))
STRUCT_INFO_END(MESH_CHUNK_DESC_0745)

STRUCT_INFO_BEGIN(MESH_CHUNK_DESC_0801)
STRUCT_VAR_INFO(nFlags, TYPE_INFO(int))
STRUCT_VAR_INFO(nFlags2, TYPE_INFO(int))
STRUCT_VAR_INFO(nVerts, TYPE_INFO(int))
STRUCT_VAR_INFO(nIndices, TYPE_INFO(int))
STRUCT_VAR_INFO(nSubsets, TYPE_INFO(int))
STRUCT_VAR_INFO(nSubsetsChunkId, TYPE_INFO(int))
STRUCT_VAR_INFO(nVertAnimID, TYPE_INFO(int))
STRUCT_VAR_INFO(nStreamChunkID, TYPE_ARRAY(16, TYPE_INFO(int)))
STRUCT_VAR_INFO(nPhysicsDataChunkId, TYPE_ARRAY(4, TYPE_INFO(int)))
STRUCT_VAR_INFO(bboxMin, TYPE_INFO(Vec3))
STRUCT_VAR_INFO(bboxMax, TYPE_INFO(Vec3))
STRUCT_VAR_INFO(texMappingDensity, TYPE_INFO(float))
STRUCT_VAR_INFO(geometricMeanFaceArea, TYPE_INFO(float))
STRUCT_VAR_INFO(reserved, TYPE_ARRAY(30, TYPE_INFO(int)))
STRUCT_INFO_END(MESH_CHUNK_DESC_0801)

STRUCT_INFO_BEGIN(MESH_CHUNK_DESC_0802)
STRUCT_VAR_INFO(nFlags, TYPE_INFO(int))
STRUCT_VAR_INFO(nFlags2, TYPE_INFO(int))
STRUCT_VAR_INFO(nVerts, TYPE_INFO(int))
STRUCT_VAR_INFO(nIndices, TYPE_INFO(int))
STRUCT_VAR_INFO(nSubsets, TYPE_INFO(int))
STRUCT_VAR_INFO(nSubsetsChunkId, TYPE_INFO(int))
STRUCT_VAR_INFO(nVertAnimID, TYPE_INFO(int))
STRUCT_VAR_INFO(nStreamChunkID, TYPE_ARRAY(16, TYPE_ARRAY(8, TYPE_INFO(int))))
STRUCT_VAR_INFO(nPhysicsDataChunkId, TYPE_ARRAY(4, TYPE_INFO(int)))
STRUCT_VAR_INFO(bboxMin, TYPE_INFO(Vec3))
STRUCT_VAR_INFO(bboxMax, TYPE_INFO(Vec3))
STRUCT_VAR_INFO(texMappingDensity, TYPE_INFO(float))
STRUCT_VAR_INFO(geometricMeanFaceArea, TYPE_INFO(float))
STRUCT_VAR_INFO(reserved, TYPE_ARRAY(30, TYPE_INFO(int)))
STRUCT_INFO_END(MESH_CHUNK_DESC_0802)

STRUCT_INFO_BEGIN(STREAM_DATA_CHUNK_DESC_0800)
STRUCT_VAR_INFO(nFlags, TYPE_INFO(int))
STRUCT_VAR_INFO(nStreamType, TYPE_INFO(int))
STRUCT_VAR_INFO(nCount, TYPE_INFO(int))
STRUCT_VAR_INFO(nElementSize, TYPE_INFO(int))
STRUCT_VAR_INFO(reserved, TYPE_ARRAY(2, TYPE_INFO(int)))
STRUCT_INFO_END(STREAM_DATA_CHUNK_DESC_0800)

STRUCT_INFO_BEGIN(STREAM_DATA_CHUNK_DESC_0801)
STRUCT_VAR_INFO(nFlags, TYPE_INFO(int))
STRUCT_VAR_INFO(nStreamType, TYPE_INFO(int))
STRUCT_VAR_INFO(nStreamIndex, TYPE_INFO(int))
STRUCT_VAR_INFO(nCount, TYPE_INFO(int))
STRUCT_VAR_INFO(nElementSize, TYPE_INFO(int))
STRUCT_VAR_INFO(reserved, TYPE_ARRAY(2, TYPE_INFO(int)))
STRUCT_INFO_END(STREAM_DATA_CHUNK_DESC_0801)

STRUCT_INFO_BEGIN(MESH_SUBSETS_CHUNK_DESC_0800::MeshSubset)
STRUCT_VAR_INFO(nFirstIndexId, TYPE_INFO(int))
STRUCT_VAR_INFO(nNumIndices, TYPE_INFO(int))
STRUCT_VAR_INFO(nFirstVertId, TYPE_INFO(int))
STRUCT_VAR_INFO(nNumVerts, TYPE_INFO(int))
STRUCT_VAR_INFO(nMatID, TYPE_INFO(int))
STRUCT_VAR_INFO(fRadius, TYPE_INFO(float))
STRUCT_VAR_INFO(vCenter, TYPE_INFO(Vec3))
STRUCT_INFO_END(MESH_SUBSETS_CHUNK_DESC_0800::MeshSubset)

STRUCT_INFO_BEGIN(MESH_SUBSETS_CHUNK_DESC_0800::MeshBoneIDs)
STRUCT_VAR_INFO(numBoneIDs, TYPE_INFO(uint32))
STRUCT_VAR_INFO(arrBoneIDs, TYPE_ARRAY(128, TYPE_INFO(uint16)))
STRUCT_INFO_END(MESH_SUBSETS_CHUNK_DESC_0800::MeshBoneIDs)

STRUCT_INFO_BEGIN(MESH_SUBSETS_CHUNK_DESC_0800::MeshSubsetTexelDensity)
STRUCT_VAR_INFO(texelDensity, TYPE_INFO(float))
STRUCT_INFO_END(MESH_SUBSETS_CHUNK_DESC_0800::MeshSubsetTexelDensity)


STRUCT_INFO_BEGIN(MESH_SUBSETS_CHUNK_DESC_0800)
STRUCT_VAR_INFO(nFlags, TYPE_INFO(int))
STRUCT_VAR_INFO(nCount, TYPE_INFO(int))
STRUCT_VAR_INFO(reserved, TYPE_ARRAY(2, TYPE_INFO(int)))
STRUCT_INFO_END(MESH_SUBSETS_CHUNK_DESC_0800)

STRUCT_INFO_BEGIN(MESH_PHYSICS_DATA_CHUNK_DESC_0800)
STRUCT_VAR_INFO(nDataSize, TYPE_INFO(int))
STRUCT_VAR_INFO(nFlags, TYPE_INFO(int))
STRUCT_VAR_INFO(nTetrahedraDataSize, TYPE_INFO(int))
STRUCT_VAR_INFO(nTetrahedraChunkId, TYPE_INFO(int))
STRUCT_VAR_INFO(reserved, TYPE_ARRAY(2, TYPE_INFO(int)))
STRUCT_INFO_END(MESH_PHYSICS_DATA_CHUNK_DESC_0800)

STRUCT_INFO_BEGIN(BONEANIM_CHUNK_DESC_0290)
STRUCT_VAR_INFO(nBones, TYPE_INFO(int))
STRUCT_INFO_END(BONEANIM_CHUNK_DESC_0290)

STRUCT_INFO_BEGIN(BONENAMELIST_CHUNK_DESC_0745)
STRUCT_VAR_INFO(numEntities, TYPE_INFO(int))
STRUCT_INFO_END(BONENAMELIST_CHUNK_DESC_0745)

STRUCT_INFO_BEGIN(COMPILED_BONE_CHUNK_DESC_0800)
STRUCT_VAR_INFO(reserved, TYPE_ARRAY(32, TYPE_INFO(char)))
STRUCT_INFO_END(COMPILED_BONE_CHUNK_DESC_0800)

STRUCT_INFO_BEGIN(COMPILED_PHYSICALBONE_CHUNK_DESC_0800)
STRUCT_VAR_INFO(reserved, TYPE_ARRAY(32, TYPE_INFO(char)))
STRUCT_INFO_END(COMPILED_PHYSICALBONE_CHUNK_DESC_0800)

STRUCT_INFO_BEGIN(COMPILED_PHYSICALPROXY_CHUNK_DESC_0800)
STRUCT_VAR_INFO(numPhysicalProxies, TYPE_INFO(uint32))
STRUCT_INFO_END(COMPILED_PHYSICALPROXY_CHUNK_DESC_0800)

STRUCT_INFO_BEGIN(COMPILED_MORPHTARGETS_CHUNK_DESC_0800)
STRUCT_VAR_INFO(numMorphTargets, TYPE_INFO(uint32))
STRUCT_INFO_END(COMPILED_MORPHTARGETS_CHUNK_DESC_0800)

STRUCT_INFO_BEGIN(COMPILED_INTSKINVERTICES_CHUNK_DESC_0800)
STRUCT_VAR_INFO(reserved, TYPE_ARRAY(32, TYPE_INFO(char)))
STRUCT_INFO_END(COMPILED_INTSKINVERTICES_CHUNK_DESC_0800)

STRUCT_INFO_BEGIN(BaseKey)
STRUCT_VAR_INFO(time, TYPE_INFO(int))
STRUCT_INFO_END(BaseKey)

STRUCT_INFO_BEGIN(BaseTCB)
STRUCT_VAR_INFO(t, TYPE_INFO(float))
STRUCT_VAR_INFO(c, TYPE_INFO(float))
STRUCT_VAR_INFO(b, TYPE_INFO(float))
STRUCT_VAR_INFO(ein, TYPE_INFO(float))
STRUCT_VAR_INFO(eout, TYPE_INFO(float))
STRUCT_INFO_END(BaseTCB)

STRUCT_INFO_BEGIN(BaseKey3)
STRUCT_BASE_INFO(BaseKey)
STRUCT_VAR_INFO(val, TYPE_INFO(Vec3))
STRUCT_INFO_END(BaseKey3)

STRUCT_INFO_BEGIN(BaseKeyQ)
STRUCT_BASE_INFO(BaseKey)
STRUCT_VAR_INFO(val, TYPE_INFO(CryQuat))
STRUCT_INFO_END(BaseKeyQ)

STRUCT_INFO_BEGIN(CryTCB3Key)
STRUCT_BASE_INFO(BaseKey3)
STRUCT_BASE_INFO(BaseTCB)
STRUCT_INFO_END(CryTCB3Key)

STRUCT_INFO_BEGIN(CryTCBQKey)
STRUCT_BASE_INFO(BaseKeyQ)
STRUCT_BASE_INFO(BaseTCB)
STRUCT_INFO_END(CryTCBQKey)

STRUCT_INFO_BEGIN(CryKeyPQLog)
STRUCT_VAR_INFO(nTime, TYPE_INFO(int))
STRUCT_VAR_INFO(vPos, TYPE_INFO(Vec3))
STRUCT_VAR_INFO(vRotLog, TYPE_INFO(Vec3))
STRUCT_INFO_END(CryKeyPQLog)

ENUM_INFO_BEGIN(CtrlTypes)
ENUM_ELEM_INFO(, CTRL_NONE)
ENUM_ELEM_INFO(, CTRL_CRYBONE)
ENUM_ELEM_INFO(, CTRL_LINEER1)
ENUM_ELEM_INFO(, CTRL_LINEER3)
ENUM_ELEM_INFO(, CTRL_LINEERQ)
ENUM_ELEM_INFO(, CTRL_BEZIER1)
ENUM_ELEM_INFO(, CTRL_BEZIER3)
ENUM_ELEM_INFO(, CTRL_BEZIERQ)
ENUM_ELEM_INFO(, CTRL_TCB1)
ENUM_ELEM_INFO(, CTRL_TCB3)
ENUM_ELEM_INFO(, CTRL_TCBQ)
ENUM_ELEM_INFO(, CTRL_BSPLINE_2O)
ENUM_ELEM_INFO(, CTRL_BSPLINE_1O)
ENUM_ELEM_INFO(, CTRL_BSPLINE_2C)
ENUM_ELEM_INFO(, CTRL_BSPLINE_1C)
ENUM_ELEM_INFO(, CTRL_CONST)
ENUM_INFO_END(CtrlTypes)

STRUCT_INFO_BEGIN(CONTROLLER_CHUNK_DESC_0826)
STRUCT_VAR_INFO(type, TYPE_INFO(CtrlTypes))
STRUCT_VAR_INFO(nKeys, TYPE_INFO(int))
STRUCT_VAR_INFO(nFlags, TYPE_INFO(unsigned int))
STRUCT_VAR_INFO(nControllerId, TYPE_INFO(unsigned int))
STRUCT_INFO_END(CONTROLLER_CHUNK_DESC_0826)

STRUCT_INFO_BEGIN(CONTROLLER_CHUNK_DESC_0827)
STRUCT_VAR_INFO(numKeys, TYPE_INFO(unsigned int))
STRUCT_VAR_INFO(nControllerId, TYPE_INFO(unsigned int))
STRUCT_INFO_END(CONTROLLER_CHUNK_DESC_0827)

STRUCT_INFO_BEGIN(CONTROLLER_CHUNK_DESC_0829)
STRUCT_VAR_INFO(nControllerId, TYPE_INFO(unsigned int))
STRUCT_VAR_INFO(numRotationKeys, TYPE_INFO(uint16))
STRUCT_VAR_INFO(numPositionKeys, TYPE_INFO(uint16))
STRUCT_VAR_INFO(RotationFormat, TYPE_INFO(uint8))
STRUCT_VAR_INFO(RotationTimeFormat, TYPE_INFO(uint8))
STRUCT_VAR_INFO(PositionFormat, TYPE_INFO(uint8))
STRUCT_VAR_INFO(PositionKeysInfo, TYPE_INFO(uint8))
STRUCT_VAR_INFO(PositionTimeFormat, TYPE_INFO(uint8))
STRUCT_VAR_INFO(TracksAligned, TYPE_INFO(uint8))
STRUCT_INFO_END(CONTROLLER_CHUNK_DESC_0829)

STRUCT_INFO_BEGIN(CONTROLLER_CHUNK_DESC_0830)
STRUCT_VAR_INFO(numKeys, TYPE_INFO(unsigned int))
STRUCT_VAR_INFO(nFlags, Type_info(unsigned int))
STRUCT_VAR_INFO(nControllerId, TYPE_INFO(unsigned int))
STRUCT_INFO_END(CONTROLLER_CHUNK_DESC_0830)

STRUCT_INFO_BEGIN(CONTROLLER_CHUNK_DESC_0831)
STRUCT_VAR_INFO(nControllerId, TYPE_INFO(unsigned int))
STRUCT_VAR_INFO(nFlags, Type_info(unsigned int))
STRUCT_VAR_INFO(numRotationKeys, TYPE_INFO(uint16))
STRUCT_VAR_INFO(numPositionKeys, TYPE_INFO(uint16))
STRUCT_VAR_INFO(RotationFormat, TYPE_INFO(uint8))
STRUCT_VAR_INFO(RotationTimeFormat, TYPE_INFO(uint8))
STRUCT_VAR_INFO(PositionFormat, TYPE_INFO(uint8))
STRUCT_VAR_INFO(PositionKeysInfo, TYPE_INFO(uint8))
STRUCT_VAR_INFO(PositionTimeFormat, TYPE_INFO(uint8))
STRUCT_VAR_INFO(TracksAligned, TYPE_INFO(uint8))
STRUCT_INFO_END(CONTROLLER_CHUNK_DESC_0831)

STRUCT_INFO_BEGIN(CONTROLLER_CHUNK_DESC_0905)
STRUCT_VAR_INFO(numKeyPos, TYPE_INFO(uint32))
STRUCT_VAR_INFO(numKeyRot, TYPE_INFO(uint32))
STRUCT_VAR_INFO(numKeyTime, TYPE_INFO(uint32))
STRUCT_VAR_INFO(numAnims, TYPE_INFO(uint32))
STRUCT_INFO_END(CONTROLLER_CHUNK_DESC_0905)

STRUCT_INFO_BEGIN(NODE_CHUNK_DESC_0824)
STRUCT_VAR_INFO(name, TYPE_ARRAY(64, TYPE_INFO(char)))
STRUCT_VAR_INFO(ObjectID, TYPE_INFO(int))
STRUCT_VAR_INFO(ParentID, TYPE_INFO(int))
STRUCT_VAR_INFO(nChildren, TYPE_INFO(int))
STRUCT_VAR_INFO(MatID, TYPE_INFO(int))
STRUCT_VAR_INFO(_obsoleteA_, TYPE_ARRAY(4, TYPE_INFO(uint8)))
STRUCT_VAR_INFO(tm, TYPE_ARRAY(4, TYPE_ARRAY(4, TYPE_INFO(float))))
STRUCT_VAR_INFO(_obsoleteB_, TYPE_ARRAY(3, TYPE_INFO(float)))
STRUCT_VAR_INFO(_obsoleteC_, TYPE_ARRAY(4, TYPE_INFO(float)))
STRUCT_VAR_INFO(_obsoleteD_, TYPE_ARRAY(3, TYPE_INFO(float)))
STRUCT_VAR_INFO(pos_cont_id, TYPE_INFO(int))
STRUCT_VAR_INFO(rot_cont_id, TYPE_INFO(int))
STRUCT_VAR_INFO(scl_cont_id, TYPE_INFO(int))
STRUCT_VAR_INFO(PropStrLen, TYPE_INFO(int))
STRUCT_INFO_END(NODE_CHUNK_DESC_0824)

ENUM_INFO_BEGIN(HelperTypes)
ENUM_ELEM_INFO(, HP_POINT)
ENUM_ELEM_INFO(, HP_DUMMY)
ENUM_ELEM_INFO(, HP_XREF)
ENUM_ELEM_INFO(, HP_CAMERA)
ENUM_ELEM_INFO(, HP_GEOMETRY)
ENUM_INFO_END(HelperTypes)

STRUCT_INFO_BEGIN(HELPER_CHUNK_DESC_0744)
STRUCT_VAR_INFO(type, TYPE_INFO(HelperTypes))
STRUCT_VAR_INFO(size, TYPE_INFO(Vec3))
STRUCT_INFO_END(HELPER_CHUNK_DESC_0744)

STRUCT_INFO_BEGIN(MESHMORPHTARGET_CHUNK_DESC_0001)
STRUCT_VAR_INFO(nChunkIdMesh, TYPE_INFO(unsigned int))
STRUCT_VAR_INFO(numMorphVertices, TYPE_INFO(unsigned int))
STRUCT_INFO_END(MESHMORPHTARGET_CHUNK_DESC_0001)

STRUCT_INFO_BEGIN(SMeshMorphTargetVertex)
STRUCT_VAR_INFO(nVertexId, TYPE_INFO(unsigned int))
STRUCT_VAR_INFO(ptVertex, TYPE_INFO(Vec3))
STRUCT_INFO_END(SMeshMorphTargetVertex)

STRUCT_INFO_BEGIN(SMeshMorphTargetHeader)
STRUCT_VAR_INFO(MeshID, TYPE_INFO(uint32))
STRUCT_VAR_INFO(NameLength, TYPE_INFO(uint32))
STRUCT_VAR_INFO(numIntVertices, TYPE_INFO(uint32))
STRUCT_VAR_INFO(numExtVertices, TYPE_INFO(uint32))
STRUCT_INFO_END(SMeshMorphTargetHeader)

STRUCT_INFO_BEGIN(SMeshPhysicalProxyHeader)
STRUCT_VAR_INFO(ChunkID, TYPE_INFO(uint32))
STRUCT_VAR_INFO(numPoints, TYPE_INFO(uint32))
STRUCT_VAR_INFO(numIndices, TYPE_INFO(uint32))
STRUCT_VAR_INFO(numMaterials, TYPE_INFO(uint32))
STRUCT_INFO_END(SMeshPhysicalProxyHeader)

STRUCT_INFO_BEGIN(BONEINITIALPOS_CHUNK_DESC_0001)
STRUCT_VAR_INFO(nChunkIdMesh, TYPE_INFO(unsigned int))
STRUCT_VAR_INFO(numBones, TYPE_INFO(unsigned int))
STRUCT_INFO_END(BONEINITIALPOS_CHUNK_DESC_0001)

STRUCT_INFO_BEGIN(SBoneInitPosMatrix)
STRUCT_VAR_INFO(mx, TYPE_ARRAY(4, TYPE_ARRAY(3, TYPE_INFO(float))))
STRUCT_INFO_END(SBoneInitPosMatrix)

STRUCT_INFO_BEGIN(EXPORT_FLAGS_CHUNK_DESC)
STRUCT_VAR_INFO(flags, TYPE_INFO(unsigned int))
STRUCT_VAR_INFO(rc_version, TYPE_ARRAY(4, TYPE_INFO(unsigned int)))
STRUCT_VAR_INFO(rc_version_string, TYPE_ARRAY(16, TYPE_INFO(char)))
STRUCT_VAR_INFO(assetAuthorTool, TYPE_INFO(uint32))
STRUCT_VAR_INFO(authorToolVersion, TYPE_INFO(uint32))
STRUCT_VAR_INFO(reserved, TYPE_ARRAY(30, TYPE_INFO(unsigned int)))
STRUCT_INFO_END(EXPORT_FLAGS_CHUNK_DESC)

STRUCT_INFO_BEGIN(BREAKABLE_PHYSICS_CHUNK_DESC)
STRUCT_VAR_INFO(granularity, TYPE_INFO(unsigned int))
STRUCT_VAR_INFO(nMode, TYPE_INFO(int))
STRUCT_VAR_INFO(nRetVtx, TYPE_INFO(int))
STRUCT_VAR_INFO(nRetTets, TYPE_INFO(int))
STRUCT_VAR_INFO(nReserved, TYPE_ARRAY(10, TYPE_INFO(int)))
STRUCT_INFO_END(BREAKABLE_PHYSICS_CHUNK_DESC)

STRUCT_INFO_BEGIN(FOLIAGE_INFO_CHUNK_DESC)
STRUCT_VAR_INFO(nSpines, TYPE_INFO(int))
STRUCT_VAR_INFO(nSpineVtx, TYPE_INFO(int))
STRUCT_VAR_INFO(nSkinnedVtx, TYPE_INFO(int))
STRUCT_VAR_INFO(nBoneIds, TYPE_INFO(int))
STRUCT_INFO_END(FOLIAGE_INFO_CHUNK_DESC)

STRUCT_INFO_BEGIN(FOLIAGE_SPINE_SUB_CHUNK)
STRUCT_VAR_INFO(nVtx, TYPE_INFO(char))
STRUCT_VAR_INFO(len, TYPE_INFO(float))
STRUCT_VAR_INFO(navg, TYPE_INFO(Vec3))
STRUCT_VAR_INFO(iAttachSpine, TYPE_INFO(unsigned char))
STRUCT_VAR_INFO(iAttachSeg, TYPE_INFO(unsigned char))
STRUCT_INFO_END(FOLIAGE_SPINE_SUB_CHUNK)

#endif // CRYINCLUDE_CRYCOMMON_CRYHEADERS_INFO_H
