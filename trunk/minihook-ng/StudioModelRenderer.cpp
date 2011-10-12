#include <windows.h>
#include "SDKInclude.h"
#include "TransInclude.h"
#include "client.h"

// This pointer to CStudioModelRenderer class !
StudioModelRenderer_d pThis;

//=========================
// StudioDrawModel
//=========================
int StudioDrawModel (int flags)
{
	return oStudioDrawModel(flags);
}

//=========================
// StudioDrawPlayer
//=========================
int StudioDrawPlayer(int flags, struct entity_state_s *pplayer)
{
	return oStudioDrawPlayer(flags, pplayer);
}

//=========================
// StudioGetAnim
// Look up animation data for sequence
//=========================
mstudioanim_t StudioGetAnim( model_t *m_pSubModel, mstudioseqdesc_t *pseqdesc )
{
	return oStudioGetAnim(m_pSubModel, pseqdesc);
}

//=========================
// StudioSetUpTransform
// Interpolate model position and angles and set up matrices
//=========================
void StudioSetUpTransform (int trivial_accept)
{
	oStudioSetUpTransform(trivial_accept);
}

//=========================
// StudioSetupBones
// Set up model bone positions
//=========================
void StudioSetupBones ( void )
{
	oStudioSetupBones();
}

//=========================
// StudioCalcAttachments
// Find final attachment points
//=========================
void StudioCalcAttachments ( void )
{
	oStudioCalcAttachments();
}

//=========================
// StudioSaveBones
// Save bone matrices and names
//=========================
void StudioSaveBones( void )
{
	oStudioSaveBones();
}

//=========================
// StudioMergeBones
// Merge cached bones with current bones for model
//=========================
void StudioMergeBones( model_t *m_pSubModel )
{
	oStudioMergeBones(m_pSubModel);
}

//=========================
// StudioEstimateInterpolant
// Determine interpolation fraction
//=========================
float StudioEstimateInterpolant( void )
{
	return oStudioEstimateInterpolant();
}

//=========================
// StudioEstimateFrame
// Determine current frame for rendering
//=========================
float StudioEstimateFrame( mstudioseqdesc_t *pseqdesc )
{
	return oStudioEstimateFrame(pseqdesc);
}

//=========================
// StudioFxTransform
// Apply special effects to transform matrix
//=========================
void StudioFxTransform( cl_entity_t *ent, float transform[3][4] )
{
	oStudioFxTransform(ent, transform);
}

//=========================
// StudioSlerpBones
// Spherical interpolation of bones
//=========================
void StudioSlerpBones( vec4_t q1[], float pos1[][3], vec4_t q2[], float pos2[][3], float s )
{
	oStudioSlerpBones(q1, pos1, q2, pos2, s);
}

//=========================
// StudioCalcBoneAdj
// Compute bone adjustments ( bone controllers )
//=========================
void StudioCalcBoneAdj ( float dadt, float *adj, const byte *pcontroller1, const byte *pcontroller2, byte mouthopen )
{
	oStudioCalcBoneAdj(dadt, adj, pcontroller1, pcontroller2, mouthopen);
}

//=========================
// StudioCalcBoneQuaterion
// Get bone quaternions
//=========================
void StudioCalcBoneQuaterion( int frame, float s, mstudiobone_t *pbone, mstudioanim_t *panim, float *adj, float *q )
{
	oStudioCalcBoneQuaterion(frame, s, pbone, panim, adj, q);
}

//=========================
// StudioCalcBonePosition
// Get bone positions
//=========================
void StudioCalcBonePosition( int frame, float s, mstudiobone_t *pbone, mstudioanim_t *panim, float *adj, float *pos )
{
	oStudioCalcBonePosition(frame, s, pbone, panim, adj, pos);
}

//=========================
// StudioCalcRotations
// Compute rotations
//=========================
void StudioCalcRotations( float pos[][3], vec4_t *q, mstudioseqdesc_t *pseqdesc, mstudioanim_t *panim, float f )
{
	oStudioCalcRotations(pos, q, pseqdesc, panim, f);
}

//=========================
// StudioCheckBBox
// Check if entity's bbox is
// in the view frustrum
//=========================
bool StudioCheckBBox ( void )
{
/*	cl_entity_t* ent = gStudio.GetCurrentEntity();
	if(cvar.gsaim && ent && ent->player)
	{
		return true;
	}*/

	return gStudio.StudioCheckBBox();
}

//=========================
// StudioRenderModel
// Send bones and verts to renderer
//=========================
extern int team;
void StudioRenderModel ( void )
{
	int plindex;

	cl_entity_s* ent = gStudio.GetCurrentEntity();

	if(cvar.lambert)
	{
		if(ent && ent->player)
		{
			team = vPlayers[ent->index].team;
			if((team == TEAM_TERROR))
			{
				ent->curstate.rendercolor.r = 255;
				ent->curstate.rendercolor.g = 0;
				ent->curstate.rendercolor.b = 0;
			}
			else if((team == TEAM_CT))
			{
				ent->curstate.rendercolor.r = 0;
				ent->curstate.rendercolor.g = 0;
				ent->curstate.rendercolor.b = 255;
			}

			ent->curstate.renderamt = 1;
			glDepthFunc(GL_GREATER);
			gStudio.SetForceFaceFlags( STUDIO_NF_FULLBRIGHT ); 
			glDisable(GL_TEXTURE_2D);
			oStudioRenderFinal();
		}
	}
	else
	{
		oStudioRenderModel();
	}

	if(ent && ent->player)
	{
		plindex = ent->index;
		if(plindex != -1)
		if(!vPlayers[plindex].gotbones) //gotbones is a bool which is reset for every player in every Draw() call
		{
			model_s* pModel = gStudio.SetupPlayerModel(plindex);
			studiohdr_t* pStudioHeader = (studiohdr_t*)gStudio.Mod_Extradata( pModel );
			typedef float TransformMatrix[ MAXSTUDIOBONES ][ 3 ][ 4 ];
			TransformMatrix*  pbonetransform = (TransformMatrix*)gStudio.StudioGetBoneTransform();
			int i = 0;
			vPlayers[plindex].numTargetSpots = 52;//pStudioHeader->numbones;
			for( i=0; i < 52; i++ )
			{
				vPlayers[plindex].TargetSpots[i][ 0 ] = (*pbonetransform)[ i ][ 0 ][ 3 ];
				vPlayers[plindex].TargetSpots[i][ 1 ] = (*pbonetransform)[ i ][ 1 ][ 3 ];
				vPlayers[plindex].TargetSpots[i][ 2 ] = (*pbonetransform)[ i ][ 2 ][ 3 ];
			
			}
			vPlayers[plindex].gotbones = true;
		}
	}
}

//=========================
// StudioRenderFinal
// Finalize rendering
//=========================
void StudioRenderFinal (void)
{
	oStudioRenderFinal();
}

//=========================
// StudioRenderFinal_Software
// Software renderer finishing function
//=========================
void StudioRenderFinal_Software ( void )
{
	oStudioRenderFinal_Software();
}

//=========================
// StudioRenderFinal_Hardware
// GL&D3D renderer finishing function
//=========================
void StudioRenderFinal_Hardware ( void )
{
	oStudioRenderFinal_Hardware();
}

//=========================
// StudioPlayerBlend
// Determine pitch and blending amounts for players
//=========================
void StudioPlayerBlend ( mstudioseqdesc_t *pseqdesc, int *pBlend, float *pPitch )
{
	oStudioPlayerBlend(pseqdesc, pBlend, pPitch);
}

//=========================
// StudioEstimateGait
// Estimate gait frame for player
//=========================
void StudioEstimateGait ( entity_state_t *pplayer )
{
	oStudioEstimateGait(pplayer);
}

//=========================
// StudioProcessGait
// Process movement of player
//=========================
void StudioProcessGait ( entity_state_t *pplayer )
{
	oStudioProcessGait(pplayer);
}

//===================================================================================
// Callgates & Patchgates
//===================================================================================
void __declspec(naked) oStudioRenderModel(void)
{
	_asm
	{
		mov ecx, pThis
		jmp gStudioModelRenderer.StudioRenderModel;
	}
}
void __declspec(naked)StudioRenderModel_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioRenderModel
	}
}

int __declspec(naked) oStudioDrawModel(int flags)
{
	_asm
	{
		mov ecx, pThis
		jmp gStudioModelRenderer.StudioDrawModel;
	}
}
void __declspec(naked) StudioDrawModel_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioDrawModel
	}
}

int __declspec(naked) oStudioDrawPlayer(int flags, struct entity_state_s *pplayer)
{
	_asm
	{
		mov ecx, pThis
		jmp gStudioModelRenderer.StudioDrawPlayer;
	}
}
void __declspec(naked) StudioDrawPlayer_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioDrawPlayer
	}
}

mstudioanim_t __declspec(naked) oStudioGetAnim(model_t *m_pSubModel, mstudioseqdesc_t *pseqdesc)
{
	_asm
	{
		mov ecx, pThis
		jmp gStudioModelRenderer.StudioGetAnim;
	}
}
void __declspec(naked) StudioGetAnim_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioGetAnim
	}
}

void __declspec(naked) oStudioSetUpTransform(int trivial_accept)
{
	_asm
	{
		mov ecx, pThis
		jmp gStudioModelRenderer.StudioSetUpTransform;
	}
}
void __declspec(naked) StudioSetUpTransform_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioSetUpTransform
	}
}

void __declspec(naked) oStudioSetupBones(void)
{
	_asm
	{
		mov ecx, pThis
		jmp gStudioModelRenderer.StudioSetupBones;
	}
}
void __declspec(naked) StudioSetupBones_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioSetupBones
	}
}

void __declspec(naked) oStudioCalcAttachments(void)
{
	_asm
	{
		mov ecx, pThis
		jmp gStudioModelRenderer.StudioCalcAttachments;
	}
}
void __declspec(naked) StudioCalcAttachments_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioCalcAttachments
	}
}

void __declspec(naked) oStudioSaveBones(void)
{
	_asm
	{
		mov ecx, pThis
		jmp gStudioModelRenderer.StudioSaveBones;
	}
}
void __declspec(naked) StudioSaveBones_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioSaveBones
	}
}

void __declspec(naked) oStudioMergeBones(model_t *m_pSubModel)
{
	_asm
	{
		mov ecx, pThis
		jmp gStudioModelRenderer.StudioMergeBones;
	}
}
void __declspec(naked) StudioMergeBones_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioMergeBones
	}
}

float __declspec(naked) oStudioEstimateInterpolant(void)
{
	_asm
	{
		mov ecx, pThis
		jmp gStudioModelRenderer.StudioEstimateInterpolant;
	}
}
void __declspec(naked) StudioEstimateInterpolant_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioEstimateInterpolant
	}
}

float __declspec(naked) oStudioEstimateFrame(mstudioseqdesc_t *pseqdesc)
{
	_asm
	{
		mov ecx, pThis
		jmp gStudioModelRenderer.StudioEstimateFrame;
	}
}
void __declspec(naked) StudioEstimateFrame_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioEstimateFrame
	}
}

void __declspec(naked) oStudioFxTransform(cl_entity_t *ent, float transform[3][4])
{
	_asm
	{
		mov ecx, pThis
		jmp gStudioModelRenderer.StudioFxTransform;
	}
}
void __declspec(naked) StudioFxTransforme_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioFxTransform
	}
}

void __declspec(naked) oStudioSlerpBones(vec4_t q1[], float pos1[][3], vec4_t q2[], float pos2[][3], float s)
{
	_asm
	{
		mov ecx, pThis
		jmp gStudioModelRenderer.StudioSlerpBones;
	}
}
void __declspec(naked) StudioSlerpBones_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioSlerpBones
	}
}

void __declspec(naked) oStudioCalcBoneAdj(float dadt, float *adj, const byte *pcontroller1, const byte *pcontroller2, byte mouthopen)
{
	_asm
	{
		mov ecx, pThis
		jmp gStudioModelRenderer.StudioCalcBoneAdj;
	}
}
void __declspec(naked) StudioCalcBoneAdj_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioCalcBoneAdj
	}
}

void __declspec(naked) oStudioCalcBoneQuaterion(int frame, float s, mstudiobone_t *pbone, mstudioanim_t *panim, float *adj, float *q)
{
	_asm
	{
		mov ecx, pThis
		jmp gStudioModelRenderer.StudioCalcBoneQuaterion;
	}
}
void __declspec(naked) StudioCalcBoneQuaterion_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioCalcBoneQuaterion
	}
}

void __declspec(naked) oStudioCalcBonePosition(int frame, float s, mstudiobone_t *pbone, mstudioanim_t *panim, float *adj, float *pos)
{
	_asm
	{
		mov ecx, pThis
		jmp gStudioModelRenderer.StudioCalcBonePosition;
	}
}
void __declspec(naked) StudioCalcBonePosition_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioCalcBonePosition
	}
}

void __declspec(naked) oStudioCalcRotations(float pos[][3], vec4_t *q, mstudioseqdesc_t *pseqdesc, mstudioanim_t *panim, float f)
{
	_asm
	{
		mov ecx, pThis
		jmp gStudioModelRenderer.StudioCalcRotations;
	}
}
void __declspec(naked) StudioCalcRotations_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioCalcRotations
	}
}

void __declspec(naked) oStudioRenderFinal(void)
{
	_asm
	{
		mov ecx, pThis
		jmp gStudioModelRenderer.StudioRenderFinal;
	}
}
void __declspec(naked) StudioRenderFinal_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioRenderFinal
	}
}

void __declspec(naked) oStudioRenderFinal_Software(void)
{
	_asm
	{
		mov ecx, pThis
		jmp gStudioModelRenderer.StudioRenderFinal_Software;
	}
}
void __declspec(naked) StudioRenderFinal_Software_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioRenderFinal_Software
	}
}

void __declspec(naked) oStudioRenderFinal_Hardware(void)
{
	_asm
	{
		mov ecx, pThis
		jmp gStudioModelRenderer.StudioRenderFinal_Hardware;
	}
}
void __declspec(naked) StudioRenderFinal_Hardware_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioRenderFinal_Hardware
	}
}

void __declspec(naked) oStudioPlayerBlend(mstudioseqdesc_t *pseqdesc, int *pBlend, float *pPitch)
{
	_asm
	{
		mov ecx, pThis
		jmp gStudioModelRenderer.StudioPlayerBlend;
	}
}
void __declspec(naked) StudioPlayerBlend_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioPlayerBlend
	}
}

void __declspec(naked) oStudioEstimateGait(entity_state_t *pplayer)
{
	_asm
	{
		mov ecx, pThis
		jmp gStudioModelRenderer.StudioEstimateGait;
	}
}
void __declspec(naked) StudioEstimateGait_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioEstimateGait
	}
}

void __declspec(naked) oStudioProcessGait(entity_state_t *pplayer)
{
	_asm
	{
		mov ecx, pThis
		jmp gStudioModelRenderer.StudioProcessGait;
	}
}
void __declspec(naked) StudioProcessGait_Gate(void)
{
	_asm
	{
		mov pThis, ecx
		jmp StudioProcessGait
	}
}