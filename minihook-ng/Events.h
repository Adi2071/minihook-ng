#ifndef __EVENT__
#define __EVENT_

typedef void ( *pfnEvent )( struct event_args_s *args );
typedef void ( *pfnFireBullets )( int idx, float *forward, float *right, float *up, int cShots, float *vecSrc, float *vecDirShooting, float flDistance, int iBulletType, int iTracerFreq, int *tracerCount, float flSpreadX, float flSpreadY );

// All mods
void hEV_HLDM_FireBullets (int idx, float *forward, float *right, float *up, int cShots, float *vecSrc, float *vecDirShooting, float flDistance, int iBulletType, int iTracerFreq, int *tracerCount, float flSpreadX, float flSpreadY);
extern pfnFireBullets pEV_HLDM_FireBullets;

// Counterstrike
void hglock1 (struct event_args_s *args);
void hglock2 (struct event_args_s *args);
void hshotgun1 (struct event_args_s *args);
void hshotgun2 (struct event_args_s *args);
void hmp5 (struct event_args_s *args);
void hpython (struct event_args_s *args);
void hgauss (struct event_args_s *args);
void hgaussspin (struct event_args_s *args);
void htrain (struct event_args_s *args);
void hvehicle (struct event_args_s *args);
void husp (struct event_args_s *args);
void hmp5n (struct event_args_s *args);
void hak47 (struct event_args_s *args);
void haug (struct event_args_s *args);
void hdeagle (struct event_args_s *args);
void hg3sg1 (struct event_args_s *args);
void hsg550 (struct event_args_s *args);
void hglock18 (struct event_args_s *args);
void hm249 (struct event_args_s *args);
void hm3 (struct event_args_s *args);
void hm4a1 (struct event_args_s *args);
void hmac10 (struct event_args_s *args);
void hp90 (struct event_args_s *args);
void hp228 (struct event_args_s *args);
void hawp (struct event_args_s *args);
void hscout (struct event_args_s *args);
void hsg552 (struct event_args_s *args);
void htmp (struct event_args_s *args);
void hfiveseven (struct event_args_s *args);
void hump45 (struct event_args_s *args);
void hxm1014 (struct event_args_s *args);
void helite_left (struct event_args_s *args);
void helite_right (struct event_args_s *args);
void hknife (struct event_args_s *args);
void hgalil (struct event_args_s *args);
void hfamas (struct event_args_s *args);
void hdecal_reset (struct event_args_s *args);
void hcreatesmoke (struct event_args_s *args);
void hcreateexplo (struct event_args_s *args);

extern pfnEvent pglock1;
extern pfnEvent pglock2;
extern pfnEvent pshotgun1;
extern pfnEvent pshotgun2;
extern pfnEvent pmp5;
extern pfnEvent ppython;
extern pfnEvent pgauss;
extern pfnEvent pgaussspin;
extern pfnEvent ptrain;
extern pfnEvent pvehicle;
extern pfnEvent pusp;
extern pfnEvent pmp5n;
extern pfnEvent pak47;
extern pfnEvent paug;
extern pfnEvent pdeagle;
extern pfnEvent pg3sg1;
extern pfnEvent psg550;
extern pfnEvent pglock18;
extern pfnEvent pm249;
extern pfnEvent pm3;
extern pfnEvent pm4a1;
extern pfnEvent pmac10;
extern pfnEvent pp90;
extern pfnEvent pp228;
extern pfnEvent pawp;
extern pfnEvent pscout;
extern pfnEvent psg552;
extern pfnEvent ptmp;
extern pfnEvent pfiveseven;
extern pfnEvent pump45;
extern pfnEvent pxm1014;
extern pfnEvent pelite_left;
extern pfnEvent pelite_right;
extern pfnEvent pknife;
extern pfnEvent pgalil;
extern pfnEvent pfamas;
extern pfnEvent pdecal_reset;
extern pfnEvent pcreatesmoke;
extern pfnEvent pcreateexplo;

// DOD
void hmisc_train (struct event_args_s *args);
void hweapons_colt (struct event_args_s *args);
void hweapons_luger (struct event_args_s *args);
void hweapons_m1carbine (struct event_args_s *args);
void hweapons_garand (struct event_args_s *args);
void hweapons_scopedkar (struct event_args_s *args);
void hweapons_thompson (struct event_args_s *args);
void hweapons_mp44 (struct event_args_s *args);
void hweapons_spring (struct event_args_s *args);
void hweapons_kar (struct event_args_s *args);
void hweapons_mp40 (struct event_args_s *args);
void hweapons_knife (struct event_args_s *args);
void hweapons_bar (struct event_args_s *args);
void hweapons_mg42 (struct event_args_s *args);
void hweapons_mg34 (struct event_args_s *args);
void hweapons_30cal (struct event_args_s *args);
void hweapons_greasegun (struct event_args_s *args);
void hweapons_fg42 (struct event_args_s *args);
void hweapons_k43 (struct event_args_s *args);
void hweapons_enfield (struct event_args_s *args);
void hweapons_sten (struct event_args_s *args);
void hweapons_bren (struct event_args_s *args);
void hweapons_webley (struct event_args_s *args);
void hweapons_scopedenfield (struct event_args_s *args);
void hweapons_bazooka (struct event_args_s *args);
void hweapons_pschreck (struct event_args_s *args);
void hweapons_piat (struct event_args_s *args);
void hweapons_mortar (struct event_args_s *args);
void hweapons_melee (struct event_args_s *args);
void hmisc_pain (struct event_args_s *args);
void heffects_smoke (struct event_args_s *args);
void heffects_blood (struct event_args_s *args);
void heffects_bloodstream (struct event_args_s *args);
void heffects_tracers (struct event_args_s *args);
void heffects_bubbletrails (struct event_args_s *args);
void heffects_bubbles (struct event_args_s *args);
void heffects_explosion (struct event_args_s *args);
void heffects_sparkshower (struct event_args_s *args);
void hmisc_whizz (struct event_args_s *args);
void hmisc_usvoice (struct event_args_s *args);
void hmisc_gervoice (struct event_args_s *args);
void heffects_bodydamage (struct event_args_s *args);
void hmisc_roundrestart (struct event_args_s *args);
void hmisc_camera (struct event_args_s *args);
void heffects_helmet (struct event_args_s *args);
void hmisc_roundreset (struct event_args_s *args);
void heffects_overheat (struct event_args_s *args);
void heffects_rockettrail (struct event_args_s *args);
void heffects_mortarshell (struct event_args_s *args);

extern pfnEvent pmisc_train;
extern pfnEvent pweapons_colt;
extern pfnEvent pweapons_luger;
extern pfnEvent pweapons_m1carbine;
extern pfnEvent pweapons_garand;
extern pfnEvent pweapons_scopedkar;
extern pfnEvent pweapons_thompson;
extern pfnEvent pweapons_mp44;
extern pfnEvent pweapons_spring;
extern pfnEvent pweapons_kar;
extern pfnEvent pweapons_mp40;
extern pfnEvent pweapons_knife;
extern pfnEvent pweapons_bar;
extern pfnEvent pweapons_mg42;
extern pfnEvent pweapons_mg34;
extern pfnEvent pweapons_30cal;
extern pfnEvent pweapons_greasegun;
extern pfnEvent pweapons_fg42;
extern pfnEvent pweapons_k43;
extern pfnEvent pweapons_enfield;
extern pfnEvent pweapons_sten;
extern pfnEvent pweapons_bren;
extern pfnEvent pweapons_webley;
extern pfnEvent pweapons_scopedenfield;
extern pfnEvent pweapons_bazooka;
extern pfnEvent pweapons_pschreck;
extern pfnEvent pweapons_piat;
extern pfnEvent pweapons_mortar;
extern pfnEvent pweapons_melee;
extern pfnEvent pmisc_pain;
extern pfnEvent peffects_smoke;
extern pfnEvent peffects_blood;
extern pfnEvent peffects_bloodstream;
extern pfnEvent peffects_tracers;
extern pfnEvent peffects_bubbletrails;
extern pfnEvent peffects_bubbles;
extern pfnEvent peffects_explosion;
extern pfnEvent peffects_sparkshower;
extern pfnEvent pmisc_whizz;
extern pfnEvent pmisc_usvoice;
extern pfnEvent pmisc_gervoice;
extern pfnEvent peffects_bodydamage;
extern pfnEvent pmisc_roundrestart;
extern pfnEvent pmisc_camera;
extern pfnEvent peffects_helmet;
extern pfnEvent pmisc_roundreset;
extern pfnEvent peffects_overheat;
extern pfnEvent peffects_rockettrail;
extern pfnEvent peffects_mortarshell;

// Deathmatch Classic
void haxe (struct event_args_s *args);
void haxeswing (struct event_args_s *args);
void hrocket (struct event_args_s *args);
void hlightning (struct event_args_s *args);
void hgrenade (struct event_args_s *args);
void hspike (struct event_args_s *args);
void hsuperspike (struct event_args_s *args);
void hgibs (struct event_args_s *args);
void hteleport (struct event_args_s *args);
void htrail (struct event_args_s *args);
void hexplosion (struct event_args_s *args);
void hpowerup (struct event_args_s *args);
void hdoor_doorgoup (struct event_args_s *args);
void hdoor_doorgodown (struct event_args_s *args);
void hdoor_doorhittop (struct event_args_s *args);
void hdoor_doorhitbottom (struct event_args_s *args);

extern pfnEvent paxe;
extern pfnEvent paxeswing;
extern pfnEvent procket;
extern pfnEvent plightning;
extern pfnEvent pgrenade;
extern pfnEvent pspike;
extern pfnEvent psuperspike;
extern pfnEvent pgibs;
extern pfnEvent pteleport;
extern pfnEvent ptrail;
extern pfnEvent pexplosion;
extern pfnEvent ppowerup;
extern pfnEvent pdoor_doorgoup;
extern pfnEvent pdoor_doorgodown;
extern pfnEvent pdoor_doorhittop;
extern pfnEvent pdoor_doorhitbottom;

// Halflife
void hmp52 (struct event_args_s *args);
void hcrowbar (struct event_args_s *args);
void hcrossbow1 (struct event_args_s *args);
void hcrossbow2 (struct event_args_s *args);
void hrpg (struct event_args_s *args);
void hegon_fire (struct event_args_s *args);
void hegon_stop (struct event_args_s *args);
void hfirehornet (struct event_args_s *args);
void htripfire (struct event_args_s *args);
void hsnarkfire (struct event_args_s *args);

extern pfnEvent pmp52;
extern pfnEvent pcrowbar;
extern pfnEvent pcrossbow1;
extern pfnEvent pcrossbow2;
extern pfnEvent prpg;
extern pfnEvent pegon_fire;
extern pfnEvent pegon_stop;
extern pfnEvent pfirehornet;
extern pfnEvent ptripfire;
extern pfnEvent psnarkfire;

// Oposing force
void hegon_effect (struct event_args_s *args);
void heagle (struct event_args_s *args);
void hpenguinfire (struct event_args_s *args);
void hpipewrench (struct event_args_s *args);
void hshock (struct event_args_s *args);
void hspore (struct event_args_s *args);
void hsniper (struct event_args_s *args);
void hdisplacer (struct event_args_s *args);

extern pfnEvent pegon_effect;
extern pfnEvent peagle;
extern pfnEvent ppenguinfire;
extern pfnEvent ppipewrench;
extern pfnEvent pshock;
extern pfnEvent pspore;
extern pfnEvent psniper;
extern pfnEvent pdisplacer;

// Team fortress classic
void hwpn_tf_sniperhit (struct event_args_s *args);
void hwpn_tf_sg (struct event_args_s *args);
void hwpn_tf_sgreload (struct event_args_s *args);
void hwpn_tf_sgpump (struct event_args_s *args);
void hwpn_tf_sniper (struct event_args_s *args);
void hwpn_tf_ssg (struct event_args_s *args);
void hwpn_tf_nail (struct event_args_s *args);
void hwpn_tf_snail (struct event_args_s *args);
void hwpn_tf_rpg (struct event_args_s *args);
void hwpn_tf_ic (struct event_args_s *args);
void hwpn_tf_ar (struct event_args_s *args);
void hwpn_tf_acwu (struct event_args_s *args);
void hwpn_tf_acwd (struct event_args_s *args);
void hwpn_tf_acstart (struct event_args_s *args);
void hwpn_tf_acfire (struct event_args_s *args);
void hwpn_tf_acspin (struct event_args_s *args);
void hwpn_tf_acsspin (struct event_args_s *args);
void hwpn_tf_flame (struct event_args_s *args);
void hwpn_tf_knife (struct event_args_s *args);
void hwpn_tf_rail (struct event_args_s *args);
void hwpn_tf_tranq (struct event_args_s *args);
void hexplode_tf_nailgren (struct event_args_s *args);
void hwpn_tf_gl (struct event_args_s *args);
void hwpn_tf_pipel (struct event_args_s *args);
void hwpn_tf_axe (struct event_args_s *args);
void hwpn_tf_mednormal (struct event_args_s *args);
void hwpn_tf_medsuper (struct event_args_s *args);
void hwpn_tf_medsteam (struct event_args_s *args);
void hwpn_tf_axedecal (struct event_args_s *args);
void hmisc_tf_buildingevent (struct event_args_s *args);
void hexplode_tf_pipe (struct event_args_s *args);
void hexplode_tf_gren (struct event_args_s *args);
void hexplode_tf_engrgren (struct event_args_s *args);
void hexplode_tf_concuss (struct event_args_s *args);
void hexplode_tf_normalgren (struct event_args_s *args);
void hexplode_tf_mirvmain (struct event_args_s *args);
void hexplode_tf_mirv (struct event_args_s *args);
void hexplode_tf_fire (struct event_args_s *args);
void hexplode_tf_burn (struct event_args_s *args);
void hexplode_tf_gas (struct event_args_s *args);
void hexplode_tf_emp (struct event_args_s *args);
void hexplode_tf_ng (struct event_args_s *args);
void hmisc_gibs (struct event_args_s *args);
void hmisc_benchmark (struct event_args_s *args);

extern pfnEvent pwpn_tf_sniperhit;
extern pfnEvent pwpn_tf_sg;
extern pfnEvent pwpn_tf_sgreload;
extern pfnEvent pwpn_tf_sgpump;
extern pfnEvent pwpn_tf_sniper;
extern pfnEvent pwpn_tf_ssg;
extern pfnEvent pwpn_tf_nail;
extern pfnEvent pwpn_tf_snail;
extern pfnEvent pwpn_tf_rpg;
extern pfnEvent pwpn_tf_ic;
extern pfnEvent pwpn_tf_ar;
extern pfnEvent pwpn_tf_acwu;
extern pfnEvent pwpn_tf_acwd;
extern pfnEvent pwpn_tf_acstart;
extern pfnEvent pwpn_tf_acfire;
extern pfnEvent pwpn_tf_acspin;
extern pfnEvent pwpn_tf_acsspin;
extern pfnEvent pwpn_tf_flame;
extern pfnEvent pwpn_tf_knife;
extern pfnEvent pwpn_tf_rail;
extern pfnEvent pwpn_tf_tranq;
extern pfnEvent pexplode_tf_nailgren;
extern pfnEvent pwpn_tf_gl;
extern pfnEvent pwpn_tf_pipel;
extern pfnEvent pwpn_tf_axe;
extern pfnEvent pwpn_tf_mednormal;
extern pfnEvent pwpn_tf_medsuper;
extern pfnEvent pwpn_tf_medsteam;
extern pfnEvent pwpn_tf_axedecal;
extern pfnEvent pmisc_tf_buildingevent;
extern pfnEvent pexplode_tf_pipe;
extern pfnEvent pexplode_tf_gren;
extern pfnEvent pexplode_tf_engrgren;
extern pfnEvent pexplode_tf_concuss;
extern pfnEvent pexplode_tf_normalgren;
extern pfnEvent pexplode_tf_mirvmain;
extern pfnEvent pexplode_tf_mirv;
extern pfnEvent pexplode_tf_fire;
extern pfnEvent pexplode_tf_burn;
extern pfnEvent pexplode_tf_gas;
extern pfnEvent pexplode_tf_emp;
extern pfnEvent pexplode_tf_ng;
extern pfnEvent pmisc_gibs;
extern pfnEvent pmisc_benchmark;

#endif