#include <windows.h>
#include "SDKInclude.h"
#include "TransInclude.h"

// Counterstrike
void hglock1( struct event_args_s *args )
{
	pglock1(args);
}

void hglock2( struct event_args_s *args )
{
	pglock2(args);
}

void hshotgun1( struct event_args_s *args )
{
	pshotgun1(args);
}

void hshotgun2( struct event_args_s *args )
{
	pshotgun2(args);
}

void hmp5( struct event_args_s *args )
{
	pmp5(args);
}

void hpython( struct event_args_s *args )
{
	ppython(args);
}

void hgauss( struct event_args_s *args )
{
	pgauss(args);
}

void hgaussspin( struct event_args_s *args )
{
	pgaussspin(args);
}

void htrain( struct event_args_s *args )
{
	ptrain(args);
}

void hvehicle( struct event_args_s *args )
{
	pvehicle(args);
}

void husp( struct event_args_s *args )
{
	pusp(args);
}

void hmp5n( struct event_args_s *args )
{
	pmp5n(args);
}

void hak47( struct event_args_s *args )
{
	pak47(args);
}

void haug( struct event_args_s *args )
{
	paug(args);
}

void hdeagle( struct event_args_s *args )
{
	pdeagle(args);
}

void hg3sg1( struct event_args_s *args )
{
	pg3sg1(args);
}

void hsg550( struct event_args_s *args )
{
	psg550(args);
}

void hglock18( struct event_args_s *args )
{
	pglock18(args);
}

void hm249( struct event_args_s *args )
{
	pm249(args);
}

void hm3( struct event_args_s *args )
{
	pm3(args);
}

void hm4a1( struct event_args_s *args )
{
	pm4a1(args);
}

void hmac10( struct event_args_s *args )
{
	pmac10(args);
}

void hp90( struct event_args_s *args )
{
	pp90(args);
}

void hp228( struct event_args_s *args )
{
	pp228(args);
}

void hawp( struct event_args_s *args )
{
	pawp(args);
}

void hscout( struct event_args_s *args )
{
	pscout(args);
}

void hsg552( struct event_args_s *args )
{
	psg552(args);
}

void htmp( struct event_args_s *args )
{
	ptmp(args);
}

void hfiveseven( struct event_args_s *args )
{
	pfiveseven(args);
}

void hump45( struct event_args_s *args )
{
	pump45(args);
}

void hxm1014( struct event_args_s *args )
{
	pxm1014(args);
}

void helite_left( struct event_args_s *args )
{
	pelite_left(args);
}

void helite_right( struct event_args_s *args )
{
	pelite_right(args);
}

void hknife( struct event_args_s *args )
{
	pknife(args);
}

void hgalil( struct event_args_s *args )
{
	pgalil(args);
}

void hfamas( struct event_args_s *args )
{
	pfamas(args);
}

void hdecal_reset( struct event_args_s *args )
{
	pdecal_reset(args);
}

void hcreatesmoke( struct event_args_s *args )
{
	pcreatesmoke(args);
}

void hcreateexplo( struct event_args_s *args )
{
	pcreateexplo(args);
}

pfnEvent pglock1;
pfnEvent pglock2;
pfnEvent pshotgun1;
pfnEvent pshotgun2;
pfnEvent pmp5;
pfnEvent ppython;
pfnEvent pgauss;
pfnEvent pgaussspin;
pfnEvent ptrain;
pfnEvent pvehicle;
pfnEvent pusp;
pfnEvent pmp5n;
pfnEvent pak47;
pfnEvent paug;
pfnEvent pdeagle;
pfnEvent pg3sg1;
pfnEvent psg550;
pfnEvent pglock18;
pfnEvent pm249;
pfnEvent pm3;
pfnEvent pm4a1;
pfnEvent pmac10;
pfnEvent pp90;
pfnEvent pp228;
pfnEvent pawp;
pfnEvent pscout;
pfnEvent psg552;
pfnEvent ptmp;
pfnEvent pfiveseven;
pfnEvent pump45;
pfnEvent pxm1014;
pfnEvent pelite_left;
pfnEvent pelite_right;
pfnEvent pknife;
pfnEvent pgalil;
pfnEvent pfamas;
pfnEvent pdecal_reset;
pfnEvent pcreatesmoke;
pfnEvent pcreateexplo;

// DOD
void hmisc_train( struct event_args_s *args )
{
	pmisc_train(args);
}

void hweapons_colt( struct event_args_s *args )
{
	pweapons_colt(args);
}

void hweapons_luger( struct event_args_s *args )
{
	pweapons_luger(args);
}

void hweapons_m1carbine( struct event_args_s *args )
{
	pweapons_m1carbine(args);
}

void hweapons_garand( struct event_args_s *args )
{
	pweapons_garand(args);
}

void hweapons_scopedkar( struct event_args_s *args )
{
	pweapons_scopedkar(args);
}

void hweapons_thompson( struct event_args_s *args )
{
	pweapons_thompson(args);
}

void hweapons_mp44( struct event_args_s *args )
{
	pweapons_mp44(args);
}

void hweapons_spring( struct event_args_s *args )
{
	pweapons_spring(args);
}

void hweapons_kar( struct event_args_s *args )
{
	pweapons_kar(args);
}

void hweapons_mp40( struct event_args_s *args )
{
	pweapons_mp40(args);
}

void hweapons_knife( struct event_args_s *args )
{
	pweapons_knife(args);
}

void hweapons_bar( struct event_args_s *args )
{
	pweapons_bar(args);
}

void hweapons_mg42( struct event_args_s *args )
{
	pweapons_mg42(args);
}

void hweapons_mg34( struct event_args_s *args )
{
	pweapons_mg34(args);
}

void hweapons_30cal( struct event_args_s *args )
{
	pweapons_30cal(args);
}

void hweapons_greasegun( struct event_args_s *args )
{
	pweapons_greasegun(args);
}

void hweapons_fg42( struct event_args_s *args )
{
	pweapons_fg42(args);
}

void hweapons_k43( struct event_args_s *args )
{
	pweapons_k43(args);
}

void hweapons_enfield( struct event_args_s *args )
{
	pweapons_enfield(args);
}

void hweapons_sten( struct event_args_s *args )
{
	pweapons_sten(args);
}

void hweapons_bren( struct event_args_s *args )
{
	pweapons_bren(args);
}

void hweapons_webley( struct event_args_s *args )
{
	pweapons_webley(args);
}

void hweapons_scopedenfield( struct event_args_s *args )
{
	pweapons_scopedenfield(args);
}

void hweapons_bazooka( struct event_args_s *args )
{
	pweapons_bazooka(args);
}

void hweapons_pschreck( struct event_args_s *args )
{
	pweapons_pschreck(args);
}

void hweapons_piat( struct event_args_s *args )
{
	pweapons_piat(args);
}

void hweapons_mortar( struct event_args_s *args )
{
	pweapons_mortar(args);
}

void hweapons_melee( struct event_args_s *args )
{
	pweapons_melee(args);
}

void hmisc_pain( struct event_args_s *args )
{
	pmisc_pain(args);
}

void heffects_smoke( struct event_args_s *args )
{
	peffects_smoke(args);
}

void heffects_blood( struct event_args_s *args )
{
	peffects_blood(args);
}

void heffects_bloodstream( struct event_args_s *args )
{
	peffects_bloodstream(args);
}

void heffects_tracers( struct event_args_s *args )
{
	peffects_tracers(args);
}

void heffects_bubbletrails( struct event_args_s *args )
{
	peffects_bubbletrails(args);
}

void heffects_bubbles( struct event_args_s *args )
{
	peffects_bubbles(args);
}

void heffects_explosion( struct event_args_s *args )
{
	peffects_explosion(args);
}

void heffects_sparkshower( struct event_args_s *args )
{
	peffects_sparkshower(args);
}

void hmisc_whizz( struct event_args_s *args )
{
	pmisc_whizz(args);
}

void hmisc_usvoice( struct event_args_s *args )
{
	pmisc_usvoice(args);
}

void hmisc_gervoice( struct event_args_s *args )
{
	pmisc_gervoice(args);
}

void heffects_bodydamage( struct event_args_s *args )
{
	peffects_bodydamage(args);
}

void hmisc_roundrestart( struct event_args_s *args )
{
	pmisc_roundrestart(args);
}

void hmisc_camera( struct event_args_s *args )
{
	pmisc_camera(args);
}

void heffects_helmet( struct event_args_s *args )
{
	peffects_helmet(args);
}

void hmisc_roundreset( struct event_args_s *args )
{
	pmisc_roundreset(args);
}

void heffects_overheat( struct event_args_s *args )
{
	peffects_overheat(args);
}

void heffects_rockettrail( struct event_args_s *args )
{
	peffects_rockettrail(args);
}

void heffects_mortarshell( struct event_args_s *args )
{
	peffects_mortarshell(args);
}

pfnEvent pmisc_train;
pfnEvent pweapons_colt;
pfnEvent pweapons_luger;
pfnEvent pweapons_m1carbine;
pfnEvent pweapons_garand;
pfnEvent pweapons_scopedkar;
pfnEvent pweapons_thompson;
pfnEvent pweapons_mp44;
pfnEvent pweapons_spring;
pfnEvent pweapons_kar;
pfnEvent pweapons_mp40;
pfnEvent pweapons_knife;
pfnEvent pweapons_bar;
pfnEvent pweapons_mg42;
pfnEvent pweapons_mg34;
pfnEvent pweapons_30cal;
pfnEvent pweapons_greasegun;
pfnEvent pweapons_fg42;
pfnEvent pweapons_k43;
pfnEvent pweapons_enfield;
pfnEvent pweapons_sten;
pfnEvent pweapons_bren;
pfnEvent pweapons_webley;
pfnEvent pweapons_scopedenfield;
pfnEvent pweapons_bazooka;
pfnEvent pweapons_pschreck;
pfnEvent pweapons_piat;
pfnEvent pweapons_mortar;
pfnEvent pweapons_melee;
pfnEvent pmisc_pain;
pfnEvent peffects_smoke;
pfnEvent peffects_blood;
pfnEvent peffects_bloodstream;
pfnEvent peffects_tracers;
pfnEvent peffects_bubbletrails;
pfnEvent peffects_bubbles;
pfnEvent peffects_explosion;
pfnEvent peffects_sparkshower;
pfnEvent pmisc_whizz;
pfnEvent pmisc_usvoice;
pfnEvent pmisc_gervoice;
pfnEvent peffects_bodydamage;
pfnEvent pmisc_roundrestart;
pfnEvent pmisc_camera;
pfnEvent peffects_helmet;
pfnEvent pmisc_roundreset;
pfnEvent peffects_overheat;
pfnEvent peffects_rockettrail;
pfnEvent peffects_mortarshell;

// Deathmatch Classic
void haxe( struct event_args_s *args )
{
	paxe(args);
}

void haxeswing( struct event_args_s *args )
{
	paxeswing(args);
}

void hrocket( struct event_args_s *args )
{
	procket(args);
}

void hlightning( struct event_args_s *args )
{
	plightning(args);
}

void hgrenade( struct event_args_s *args )
{
	pgrenade(args);
}

void hspike( struct event_args_s *args )
{
	pspike(args);
}

void hsuperspike( struct event_args_s *args )
{
	psuperspike(args);
}

void hgibs( struct event_args_s *args )
{
	pgibs(args);
}

void hteleport( struct event_args_s *args )
{
	pteleport(args);
}

void htrail( struct event_args_s *args )
{
	ptrail(args);
}

void hexplosion( struct event_args_s *args )
{
	pexplosion(args);
}

void hpowerup( struct event_args_s *args )
{
	ppowerup(args);
}

void hdoor_doorgoup( struct event_args_s *args )
{
	pdoor_doorgoup(args);
}

void hdoor_doorgodown( struct event_args_s *args )
{
	pdoor_doorgodown(args);
}

void hdoor_doorhittop( struct event_args_s *args )
{
	pdoor_doorhittop(args);
}

void hdoor_doorhitbottom( struct event_args_s *args )
{
	pdoor_doorhitbottom(args);
}

pfnEvent paxe;
pfnEvent paxeswing;
pfnEvent procket;
pfnEvent plightning;
pfnEvent pgrenade;
pfnEvent pspike;
pfnEvent psuperspike;
pfnEvent pgibs;
pfnEvent pteleport;
pfnEvent ptrail;
pfnEvent pexplosion;
pfnEvent ppowerup;
pfnEvent pdoor_doorgoup;
pfnEvent pdoor_doorgodown;
pfnEvent pdoor_doorhittop;
pfnEvent pdoor_doorhitbottom;

// Halflife
void hmp52( struct event_args_s *args )
{
	pmp52(args);
}

void hcrowbar( struct event_args_s *args )
{
	pcrowbar(args);
}

void hcrossbow1( struct event_args_s *args )
{
	pcrossbow1(args);
}

void hcrossbow2( struct event_args_s *args )
{
	pcrossbow2(args);
}

void hrpg( struct event_args_s *args )
{
	prpg(args);
}

void hegon_fire( struct event_args_s *args )
{
	pegon_fire(args);
}

void hegon_stop( struct event_args_s *args )
{
	pegon_stop(args);
}

void hfirehornet( struct event_args_s *args )
{
	pfirehornet(args);
}

void htripfire( struct event_args_s *args )
{
	ptripfire(args);
}

void hsnarkfire( struct event_args_s *args )
{
	psnarkfire(args);
}

pfnEvent pmp52;
pfnEvent pcrowbar;
pfnEvent pcrossbow1;
pfnEvent pcrossbow2;
pfnEvent prpg;
pfnEvent pegon_fire;
pfnEvent pegon_stop;
pfnEvent pfirehornet;
pfnEvent ptripfire;
pfnEvent psnarkfire;

// Oposing force
void hegon_effect( struct event_args_s *args )
{
	pegon_effect(args);
}

void heagle( struct event_args_s *args )
{
	peagle(args);
}

void hpenguinfire( struct event_args_s *args )
{
	ppenguinfire(args);
}

void hpipewrench( struct event_args_s *args )
{
	ppipewrench(args);
}

void hshock( struct event_args_s *args )
{
	pshock(args);
}

void hspore( struct event_args_s *args )
{
	pspore(args);
}

void hsniper( struct event_args_s *args )
{
	psniper(args);
}

void hdisplacer( struct event_args_s *args )
{
	pdisplacer(args);
}

pfnEvent pegon_effect;
pfnEvent peagle;
pfnEvent ppenguinfire;
pfnEvent ppipewrench;
pfnEvent pshock;
pfnEvent pspore;
pfnEvent psniper;
pfnEvent pdisplacer;

// Team fortress classic
void hwpn_tf_sniperhit( struct event_args_s *args )
{
	pwpn_tf_sniperhit(args);
}

void hwpn_tf_sg( struct event_args_s *args )
{
	pwpn_tf_sg(args);
}

void hwpn_tf_sgreload( struct event_args_s *args )
{
	pwpn_tf_sgreload(args);
}

void hwpn_tf_sgpump( struct event_args_s *args )
{
	pwpn_tf_sgpump(args);
}

void hwpn_tf_sniper( struct event_args_s *args )
{
	pwpn_tf_sniper(args);
}

void hwpn_tf_ssg( struct event_args_s *args )
{
	pwpn_tf_ssg(args);
}

void hwpn_tf_nail( struct event_args_s *args )
{
	pwpn_tf_nail(args);
}

void hwpn_tf_snail( struct event_args_s *args )
{
	pwpn_tf_snail(args);
}

void hwpn_tf_rpg( struct event_args_s *args )
{
	pwpn_tf_rpg(args);
}

void hwpn_tf_ic( struct event_args_s *args )
{
	pwpn_tf_ic(args);
}

void hwpn_tf_ar( struct event_args_s *args )
{
	pwpn_tf_ar(args);
}

void hwpn_tf_acwu( struct event_args_s *args )
{
	pwpn_tf_acwu(args);
}

void hwpn_tf_acwd( struct event_args_s *args )
{
	pwpn_tf_acwd(args);
}

void hwpn_tf_acstart( struct event_args_s *args )
{
	pwpn_tf_acstart(args);
}

void hwpn_tf_acfire( struct event_args_s *args )
{
	pwpn_tf_acfire(args);
}

void hwpn_tf_acspin( struct event_args_s *args )
{
	pwpn_tf_acspin(args);
}

void hwpn_tf_acsspin( struct event_args_s *args )
{
	pwpn_tf_acsspin(args);
}

void hwpn_tf_flame( struct event_args_s *args )
{
	pwpn_tf_flame(args);
}

void hwpn_tf_knife( struct event_args_s *args )
{
	pwpn_tf_knife(args);
}

void hwpn_tf_rail( struct event_args_s *args )
{
	pwpn_tf_rail(args);
}

void hwpn_tf_tranq( struct event_args_s *args )
{
	pwpn_tf_tranq(args);
}

void hexplode_tf_nailgren( struct event_args_s *args )
{
	pexplode_tf_nailgren(args);
}

void hwpn_tf_gl( struct event_args_s *args )
{
	pwpn_tf_gl(args);
}

void hwpn_tf_pipel( struct event_args_s *args )
{
	pwpn_tf_pipel(args);
}

void hwpn_tf_axe( struct event_args_s *args )
{
	pwpn_tf_axe(args);
}

void hwpn_tf_mednormal( struct event_args_s *args )
{
	pwpn_tf_mednormal(args);
}

void hwpn_tf_medsuper( struct event_args_s *args )
{
	pwpn_tf_medsuper(args);
}

void hwpn_tf_medsteam( struct event_args_s *args )
{
	pwpn_tf_medsteam(args);
}

void hwpn_tf_axedecal( struct event_args_s *args )
{
	pwpn_tf_axedecal(args);
}

void hmisc_tf_buildingevent( struct event_args_s *args )
{
	pmisc_tf_buildingevent(args);
}

void hexplode_tf_pipe( struct event_args_s *args )
{
	pexplode_tf_pipe(args);
}

void hexplode_tf_gren( struct event_args_s *args )
{
	pexplode_tf_gren(args);
}

void hexplode_tf_engrgren( struct event_args_s *args )
{
	pexplode_tf_engrgren(args);
}

void hexplode_tf_concuss( struct event_args_s *args )
{
	pexplode_tf_concuss(args);
}

void hexplode_tf_normalgren( struct event_args_s *args )
{
	pexplode_tf_normalgren(args);
}

void hexplode_tf_mirvmain( struct event_args_s *args )
{
	pexplode_tf_mirvmain(args);
}

void hexplode_tf_mirv( struct event_args_s *args )
{
	pexplode_tf_mirv(args);
}

void hexplode_tf_fire( struct event_args_s *args )
{
	pexplode_tf_fire(args);
}

void hexplode_tf_burn( struct event_args_s *args )
{
	pexplode_tf_burn(args);
}

void hexplode_tf_gas( struct event_args_s *args )
{
	pexplode_tf_gas(args);
}

void hexplode_tf_emp( struct event_args_s *args )
{
	pexplode_tf_emp(args);
}

void hexplode_tf_ng( struct event_args_s *args )
{
	pexplode_tf_ng(args);
}

void hmisc_gibs( struct event_args_s *args )
{
	pmisc_gibs(args);
}

void hmisc_benchmark( struct event_args_s *args )
{
	pmisc_benchmark(args);
}

pfnEvent pwpn_tf_sniperhit;
pfnEvent pwpn_tf_sg;
pfnEvent pwpn_tf_sgreload;
pfnEvent pwpn_tf_sgpump;
pfnEvent pwpn_tf_sniper;
pfnEvent pwpn_tf_ssg;
pfnEvent pwpn_tf_nail;
pfnEvent pwpn_tf_snail;
pfnEvent pwpn_tf_rpg;
pfnEvent pwpn_tf_ic;
pfnEvent pwpn_tf_ar;
pfnEvent pwpn_tf_acwu;
pfnEvent pwpn_tf_acwd;
pfnEvent pwpn_tf_acstart;
pfnEvent pwpn_tf_acfire;
pfnEvent pwpn_tf_acspin;
pfnEvent pwpn_tf_acsspin;
pfnEvent pwpn_tf_flame;
pfnEvent pwpn_tf_knife;
pfnEvent pwpn_tf_rail;
pfnEvent pwpn_tf_tranq;
pfnEvent pexplode_tf_nailgren;
pfnEvent pwpn_tf_gl;
pfnEvent pwpn_tf_pipel;
pfnEvent pwpn_tf_axe;
pfnEvent pwpn_tf_mednormal;
pfnEvent pwpn_tf_medsuper;
pfnEvent pwpn_tf_medsteam;
pfnEvent pwpn_tf_axedecal;
pfnEvent pmisc_tf_buildingevent;
pfnEvent pexplode_tf_pipe;
pfnEvent pexplode_tf_gren;
pfnEvent pexplode_tf_engrgren;
pfnEvent pexplode_tf_concuss;
pfnEvent pexplode_tf_normalgren;
pfnEvent pexplode_tf_mirvmain;
pfnEvent pexplode_tf_mirv;
pfnEvent pexplode_tf_fire;
pfnEvent pexplode_tf_burn;
pfnEvent pexplode_tf_gas;
pfnEvent pexplode_tf_emp;
pfnEvent pexplode_tf_ng;
pfnEvent pmisc_gibs;
pfnEvent pmisc_benchmark;
