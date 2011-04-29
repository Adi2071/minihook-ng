#ifndef NOSPREAD_H
#define NOSPREAD_H
#include <vector>

#undef AngleVectors

class cNoSpread
{
public:
	cNoSpread(void);
	~cNoSpread(void);

	void PrimaryAttack(void);
	void DefaultSpreadVar(int weaponid);
	void HUD_PostRunCmd(struct local_state_s *from, struct local_state_s *to, struct usercmd_s *cmd, int runfuncs, double time, unsigned int random_seed);
	void GetRecoilOffset(unsigned int seed, int future, float *inangles, float *velocity, float *outangles);

	//CLocalPlayerInfo *me;
private:
	unsigned int iSeed;
	unsigned int U_Random(void);
	void U_Srand(unsigned int seed);
	float UTIL_SharedRandomFloat(unsigned int seed, float low, float high);
	void AngleVectors(const float *angles, float *forward, float *right, float *up);
	float GetVecSpread(float *velocity);
	void GetSpreadXY(unsigned int seed, int future, float *velocity, float *vec);
	DWORD BaseGun;
    int WeaponBit;
};
extern cNoSpread gNoSpread;

#endif