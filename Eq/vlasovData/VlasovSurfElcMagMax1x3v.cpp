#include <VlasovModDecl.h> 
double VlasovSurfElcMag1x3vMax_VX_P1(const double *wl, const double *wr, const double *dxvl, const double *dxvr, const double amax, const double *EM, const double *fl, const double *fr, double *outl, double *outr) 
{ 
// w: Cell-center coordinates. dxv[NDIM]: Cell spacing. amax: amax in global lax flux. E: EM field. fl/fr: Distribution function in left/right cells 
// outl/outr: output distribution function in left/right cells 
// returns abs(amid) for use in determining amax in cfl and global lax flux 
  double dv10l = 2/dxvl[1]; 
  double dv10r = 2/dxvr[1]; 
  const double *E0 = &EM[0]; 

  const double dv1 = dxvr[1], wv1 = wr[1]; 
  const double dv2 = dxvr[2], wv2 = wr[2]; 
  const double dv3 = dxvr[3], wv3 = wr[3]; 

  const double *B0 = &EM[6]; 
  const double *B1 = &EM[8]; 
  const double *B2 = &EM[10]; 

  double Ghat[5]; 

  double alpha[5]; 

  double favg[5]; 

  favg[0] = 1*fr[0]+fl[0]; 
  favg[1] = 1*fr[1]+fl[1]; 
  favg[2] = -1*fr[2]+fl[2]; 
  favg[3] = 1*fr[3]+fl[3]; 
  favg[4] = 1*fr[4]+fl[4]; 
  double fjump[5]; 

  fjump[0] = amax*(1*fr[0]-fl[0]); 
  fjump[1] = amax*(1*fr[1]-fl[1]); 
  fjump[2] = amax*(-1*fr[2]-fl[2]); 
  fjump[3] = amax*(1*fr[3]-fl[3]); 
  fjump[4] = amax*(1*fr[4]-fl[4]); 
  alpha[0] = 2.828427124746191*(B2[0]*wv2+E0[0])-2.828427124746191*B1[0]*wv3; 
  alpha[1] = 2.828427124746191*(B2[1]*wv2+E0[1])-2.828427124746191*B1[1]*wv3; 
  alpha[3] = 0.8164965809277261*B2[0]*dv2; 
  alpha[4] = -0.8164965809277261*B1[0]*dv3; 
  const double amid = 0.25*alpha[0]; 
  Ghat[0] = 0.125*(alpha[4]*favg[4]+alpha[3]*favg[3])-0.8660254037844386*fjump[2]+alpha[0]*(0.2165063509461096*favg[2]+0.125*favg[0])+0.125*alpha[1]*favg[1]-0.5*fjump[0]; 
  Ghat[1] = alpha[1]*(0.2165063509461096*favg[2]+0.125*favg[0])-0.5*fjump[1]+0.125*alpha[0]*favg[1]; 
  Ghat[3] = (-0.5*fjump[3])+0.125*alpha[0]*favg[3]+(0.2165063509461096*favg[2]+0.125*favg[0])*alpha[3]; 
  Ghat[4] = (-0.5*fjump[4])+0.125*alpha[0]*favg[4]+(0.2165063509461096*favg[2]+0.125*favg[0])*alpha[4]; 

  outr[0] += 0.5*Ghat[0]*dv10r; 
  outr[1] += 0.5*Ghat[1]*dv10r; 
  outr[2] += -0.8660254037844386*Ghat[0]*dv10r; 
  outr[3] += 0.5*Ghat[3]*dv10r; 
  outr[4] += 0.5*Ghat[4]*dv10r; 

  outl[0] += -0.5*Ghat[0]*dv10l; 
  outl[1] += -0.5*Ghat[1]*dv10l; 
  outl[2] += -0.8660254037844386*Ghat[0]*dv10l; 
  outl[3] += -0.5*Ghat[3]*dv10l; 
  outl[4] += -0.5*Ghat[4]*dv10l; 
return std::abs(amid); 
} 
double VlasovSurfElcMag1x3vMax_VX_P2(const double *wl, const double *wr, const double *dxvl, const double *dxvr, const double amax, const double *EM, const double *fl, const double *fr, double *outl, double *outr) 
{ 
// w: Cell-center coordinates. dxv[NDIM]: Cell spacing. amax: amax in global lax flux. E: EM field. fl/fr: Distribution function in left/right cells 
// outl/outr: output distribution function in left/right cells 
// returns abs(amid) for use in determining amax in cfl and global lax flux 
  double dv10l = 2/dxvl[1]; 
  double dv10r = 2/dxvr[1]; 
  const double *E0 = &EM[0]; 

  const double dv1 = dxvr[1], wv1 = wr[1]; 
  const double dv2 = dxvr[2], wv2 = wr[2]; 
  const double dv3 = dxvr[3], wv3 = wr[3]; 

  const double *B0 = &EM[9]; 
  const double *B1 = &EM[12]; 
  const double *B2 = &EM[15]; 

  double Ghat[15]; 

  double alpha[15]; 

  double favg[15]; 

  favg[0] = 1*fr[0]+fl[0]; 
  favg[1] = 1*fr[1]+fl[1]; 
  favg[2] = -1*fr[2]+fl[2]; 
  favg[3] = 1*fr[3]+fl[3]; 
  favg[4] = 1*fr[4]+fl[4]; 
  favg[5] = -1*fr[5]+fl[5]; 
  favg[6] = 1*fr[6]+fl[6]; 
  favg[7] = -1*fr[7]+fl[7]; 
  favg[8] = 1*fr[8]+fl[8]; 
  favg[9] = -1*fr[9]+fl[9]; 
  favg[10] = 1*fr[10]+fl[10]; 
  favg[11] = 1*fr[11]+fl[11]; 
  favg[12] = 1*fr[12]+fl[12]; 
  favg[13] = 1*fr[13]+fl[13]; 
  favg[14] = 1*fr[14]+fl[14]; 
  double fjump[15]; 

  fjump[0] = amax*(1*fr[0]-fl[0]); 
  fjump[1] = amax*(1*fr[1]-fl[1]); 
  fjump[2] = amax*(-1*fr[2]-fl[2]); 
  fjump[3] = amax*(1*fr[3]-fl[3]); 
  fjump[4] = amax*(1*fr[4]-fl[4]); 
  fjump[5] = amax*(-1*fr[5]-fl[5]); 
  fjump[6] = amax*(1*fr[6]-fl[6]); 
  fjump[7] = amax*(-1*fr[7]-fl[7]); 
  fjump[8] = amax*(1*fr[8]-fl[8]); 
  fjump[9] = amax*(-1*fr[9]-fl[9]); 
  fjump[10] = amax*(1*fr[10]-fl[10]); 
  fjump[11] = amax*(1*fr[11]-fl[11]); 
  fjump[12] = amax*(1*fr[12]-fl[12]); 
  fjump[13] = amax*(1*fr[13]-fl[13]); 
  fjump[14] = amax*(1*fr[14]-fl[14]); 
  alpha[0] = 2.828427124746191*(B2[0]*wv2+E0[0])-2.828427124746191*B1[0]*wv3; 
  alpha[1] = 2.828427124746191*(B2[1]*wv2+E0[1])-2.828427124746191*B1[1]*wv3; 
  alpha[3] = 0.8164965809277261*B2[0]*dv2; 
  alpha[4] = -0.8164965809277261*B1[0]*dv3; 
  alpha[6] = 0.8164965809277261*B2[1]*dv2; 
  alpha[8] = -0.8164965809277261*B1[1]*dv3; 
  alpha[11] = 2.828427124746191*(B2[2]*wv2+E0[2])-2.828427124746191*B1[2]*wv3; 
  const double amid = 0.25*alpha[0]-0.2795084971874737*alpha[11]; 
  Ghat[0] = (-1.118033988749895*fjump[12])+alpha[0]*(0.2795084971874737*favg[12]+0.2165063509461096*favg[2]+0.125*favg[0])+0.125*alpha[11]*favg[11]+alpha[4]*(0.2165063509461096*favg[9]+0.125*favg[4])+0.125*alpha[8]*favg[8]+alpha[3]*(0.2165063509461096*favg[7]+0.125*favg[3])+0.125*alpha[6]*favg[6]+alpha[1]*(0.2165063509461096*favg[5]+0.125*favg[1])-0.8660254037844386*fjump[2]-0.5*fjump[0]; 
  Ghat[1] = alpha[1]*(0.2795084971874737*favg[12]+0.1118033988749895*favg[11]+0.2165063509461096*favg[2]+0.125*favg[0])+(0.1936491673103708*favg[5]+0.1118033988749895*favg[1])*alpha[11]+alpha[8]*(0.2165063509461096*favg[9]+0.125*favg[4])+0.125*alpha[4]*favg[8]+alpha[6]*(0.2165063509461096*favg[7]+0.125*favg[3])+0.125*alpha[3]*favg[6]-0.8660254037844386*fjump[5]+alpha[0]*(0.2165063509461096*favg[5]+0.125*favg[1])-0.5*fjump[1]; 
  Ghat[3] = alpha[3]*(0.1118033988749895*favg[13]+0.2795084971874737*favg[12]+0.2165063509461096*favg[2]+0.125*favg[0])+0.125*alpha[4]*favg[10]-0.8660254037844386*fjump[7]+alpha[0]*(0.2165063509461096*favg[7]+0.125*favg[3])+0.125*alpha[1]*favg[6]+(0.2165063509461096*favg[5]+0.125*favg[1])*alpha[6]-0.5*fjump[3]; 
  Ghat[4] = alpha[4]*(0.1118033988749895*favg[14]+0.2795084971874737*favg[12]+0.2165063509461096*favg[2]+0.125*favg[0])+0.125*alpha[3]*favg[10]-0.8660254037844386*fjump[9]+alpha[0]*(0.2165063509461096*favg[9]+0.125*favg[4])+0.125*alpha[1]*favg[8]+(0.2165063509461096*favg[5]+0.125*favg[1])*alpha[8]-0.5*fjump[4]; 
  Ghat[6] = alpha[6]*(0.1118033988749895*favg[13]+0.2795084971874737*favg[12]+0.1118033988749895*favg[11]+0.2165063509461096*favg[2]+0.125*favg[0])+0.1118033988749895*favg[6]*alpha[11]+0.125*alpha[8]*favg[10]+alpha[1]*(0.2165063509461096*favg[7]+0.125*favg[3])-0.5*fjump[6]+0.125*alpha[0]*favg[6]+alpha[3]*(0.2165063509461096*favg[5]+0.125*favg[1]); 
  Ghat[8] = alpha[8]*(0.1118033988749895*favg[14]+0.2795084971874737*favg[12]+0.1118033988749895*favg[11]+0.2165063509461096*favg[2]+0.125*favg[0])+0.1118033988749895*favg[8]*alpha[11]+0.125*alpha[6]*favg[10]+alpha[1]*(0.2165063509461096*favg[9]+0.125*favg[4])-0.5*fjump[8]+0.125*alpha[0]*favg[8]+alpha[4]*(0.2165063509461096*favg[5]+0.125*favg[1]); 
  Ghat[10] = (-0.5*fjump[10])+0.125*alpha[0]*favg[10]+alpha[3]*(0.2165063509461096*favg[9]+0.125*favg[4])+0.125*(alpha[6]*favg[8]+favg[6]*alpha[8])+alpha[4]*(0.2165063509461096*favg[7]+0.125*favg[3]); 
  Ghat[11] = alpha[11]*(0.2795084971874737*favg[12]+0.07985957062499249*favg[11]+0.2165063509461096*favg[2]+0.125*favg[0])-0.5*fjump[11]+0.125*alpha[0]*favg[11]+0.1118033988749895*(alpha[8]*favg[8]+alpha[6]*favg[6])+alpha[1]*(0.1936491673103708*favg[5]+0.1118033988749895*favg[1]); 
  Ghat[13] = (-0.5*fjump[13])+0.125*alpha[0]*favg[13]+alpha[3]*(0.1936491673103708*favg[7]+0.1118033988749895*favg[3])+0.1118033988749895*alpha[6]*favg[6]; 
  Ghat[14] = (-0.5*fjump[14])+0.125*alpha[0]*favg[14]+alpha[4]*(0.1936491673103708*favg[9]+0.1118033988749895*favg[4])+0.1118033988749895*alpha[8]*favg[8]; 

  outr[0] += 0.5*Ghat[0]*dv10r; 
  outr[1] += 0.5*Ghat[1]*dv10r; 
  outr[2] += -0.8660254037844386*Ghat[0]*dv10r; 
  outr[3] += 0.5*Ghat[3]*dv10r; 
  outr[4] += 0.5*Ghat[4]*dv10r; 
  outr[5] += -0.8660254037844386*Ghat[1]*dv10r; 
  outr[6] += 0.5*Ghat[6]*dv10r; 
  outr[7] += -0.8660254037844386*Ghat[3]*dv10r; 
  outr[8] += 0.5*Ghat[8]*dv10r; 
  outr[9] += -0.8660254037844386*Ghat[4]*dv10r; 
  outr[10] += 0.5*Ghat[10]*dv10r; 
  outr[11] += 0.5*Ghat[11]*dv10r; 
  outr[12] += 1.118033988749895*Ghat[0]*dv10r; 
  outr[13] += 0.5*Ghat[13]*dv10r; 
  outr[14] += 0.5*Ghat[14]*dv10r; 

  outl[0] += -0.5*Ghat[0]*dv10l; 
  outl[1] += -0.5*Ghat[1]*dv10l; 
  outl[2] += -0.8660254037844386*Ghat[0]*dv10l; 
  outl[3] += -0.5*Ghat[3]*dv10l; 
  outl[4] += -0.5*Ghat[4]*dv10l; 
  outl[5] += -0.8660254037844386*Ghat[1]*dv10l; 
  outl[6] += -0.5*Ghat[6]*dv10l; 
  outl[7] += -0.8660254037844386*Ghat[3]*dv10l; 
  outl[8] += -0.5*Ghat[8]*dv10l; 
  outl[9] += -0.8660254037844386*Ghat[4]*dv10l; 
  outl[10] += -0.5*Ghat[10]*dv10l; 
  outl[11] += -0.5*Ghat[11]*dv10l; 
  outl[12] += -1.118033988749895*Ghat[0]*dv10l; 
  outl[13] += -0.5*Ghat[13]*dv10l; 
  outl[14] += -0.5*Ghat[14]*dv10l; 
return std::abs(amid); 
} 
double VlasovSurfElcMag1x3vMax_VX_P3(const double *wl, const double *wr, const double *dxvl, const double *dxvr, const double amax, const double *EM, const double *fl, const double *fr, double *outl, double *outr) 
{ 
// w: Cell-center coordinates. dxv[NDIM]: Cell spacing. amax: amax in global lax flux. E: EM field. fl/fr: Distribution function in left/right cells 
// outl/outr: output distribution function in left/right cells 
// returns abs(amid) for use in determining amax in cfl and global lax flux 
  double dv10l = 2/dxvl[1]; 
  double dv10r = 2/dxvr[1]; 
  const double *E0 = &EM[0]; 

  const double dv1 = dxvr[1], wv1 = wr[1]; 
  const double dv2 = dxvr[2], wv2 = wr[2]; 
  const double dv3 = dxvr[3], wv3 = wr[3]; 

  const double *B0 = &EM[12]; 
  const double *B1 = &EM[16]; 
  const double *B2 = &EM[20]; 

  double Ghat[35]; 

  double alpha[35]; 

  double favg[35]; 

  favg[0] = 1*fr[0]+fl[0]; 
  favg[1] = 1*fr[1]+fl[1]; 
  favg[2] = -1*fr[2]+fl[2]; 
  favg[3] = 1*fr[3]+fl[3]; 
  favg[4] = 1*fr[4]+fl[4]; 
  favg[5] = -1*fr[5]+fl[5]; 
  favg[6] = 1*fr[6]+fl[6]; 
  favg[7] = -1*fr[7]+fl[7]; 
  favg[8] = 1*fr[8]+fl[8]; 
  favg[9] = -1*fr[9]+fl[9]; 
  favg[10] = 1*fr[10]+fl[10]; 
  favg[11] = 1*fr[11]+fl[11]; 
  favg[12] = 1*fr[12]+fl[12]; 
  favg[13] = 1*fr[13]+fl[13]; 
  favg[14] = 1*fr[14]+fl[14]; 
  favg[15] = -1*fr[15]+fl[15]; 
  favg[16] = -1*fr[16]+fl[16]; 
  favg[17] = 1*fr[17]+fl[17]; 
  favg[18] = -1*fr[18]+fl[18]; 
  favg[19] = -1*fr[19]+fl[19]; 
  favg[20] = 1*fr[20]+fl[20]; 
  favg[21] = 1*fr[21]+fl[21]; 
  favg[22] = 1*fr[22]+fl[22]; 
  favg[23] = 1*fr[23]+fl[23]; 
  favg[24] = -1*fr[24]+fl[24]; 
  favg[25] = 1*fr[25]+fl[25]; 
  favg[26] = 1*fr[26]+fl[26]; 
  favg[27] = 1*fr[27]+fl[27]; 
  favg[28] = 1*fr[28]+fl[28]; 
  favg[29] = -1*fr[29]+fl[29]; 
  favg[30] = 1*fr[30]+fl[30]; 
  favg[31] = 1*fr[31]+fl[31]; 
  favg[32] = -1*fr[32]+fl[32]; 
  favg[33] = 1*fr[33]+fl[33]; 
  favg[34] = 1*fr[34]+fl[34]; 
  double fjump[35]; 

  fjump[0] = amax*(1*fr[0]-fl[0]); 
  fjump[1] = amax*(1*fr[1]-fl[1]); 
  fjump[2] = amax*(-1*fr[2]-fl[2]); 
  fjump[3] = amax*(1*fr[3]-fl[3]); 
  fjump[4] = amax*(1*fr[4]-fl[4]); 
  fjump[5] = amax*(-1*fr[5]-fl[5]); 
  fjump[6] = amax*(1*fr[6]-fl[6]); 
  fjump[7] = amax*(-1*fr[7]-fl[7]); 
  fjump[8] = amax*(1*fr[8]-fl[8]); 
  fjump[9] = amax*(-1*fr[9]-fl[9]); 
  fjump[10] = amax*(1*fr[10]-fl[10]); 
  fjump[11] = amax*(1*fr[11]-fl[11]); 
  fjump[12] = amax*(1*fr[12]-fl[12]); 
  fjump[13] = amax*(1*fr[13]-fl[13]); 
  fjump[14] = amax*(1*fr[14]-fl[14]); 
  fjump[15] = amax*(-1*fr[15]-fl[15]); 
  fjump[16] = amax*(-1*fr[16]-fl[16]); 
  fjump[17] = amax*(1*fr[17]-fl[17]); 
  fjump[18] = amax*(-1*fr[18]-fl[18]); 
  fjump[19] = amax*(-1*fr[19]-fl[19]); 
  fjump[20] = amax*(1*fr[20]-fl[20]); 
  fjump[21] = amax*(1*fr[21]-fl[21]); 
  fjump[22] = amax*(1*fr[22]-fl[22]); 
  fjump[23] = amax*(1*fr[23]-fl[23]); 
  fjump[24] = amax*(-1*fr[24]-fl[24]); 
  fjump[25] = amax*(1*fr[25]-fl[25]); 
  fjump[26] = amax*(1*fr[26]-fl[26]); 
  fjump[27] = amax*(1*fr[27]-fl[27]); 
  fjump[28] = amax*(1*fr[28]-fl[28]); 
  fjump[29] = amax*(-1*fr[29]-fl[29]); 
  fjump[30] = amax*(1*fr[30]-fl[30]); 
  fjump[31] = amax*(1*fr[31]-fl[31]); 
  fjump[32] = amax*(-1*fr[32]-fl[32]); 
  fjump[33] = amax*(1*fr[33]-fl[33]); 
  fjump[34] = amax*(1*fr[34]-fl[34]); 
  alpha[0] = 2.828427124746191*(B2[0]*wv2+E0[0])-2.828427124746191*B1[0]*wv3; 
  alpha[1] = 2.828427124746191*(B2[1]*wv2+E0[1])-2.828427124746191*B1[1]*wv3; 
  alpha[3] = 0.8164965809277261*B2[0]*dv2; 
  alpha[4] = -0.8164965809277261*B1[0]*dv3; 
  alpha[6] = 0.8164965809277261*B2[1]*dv2; 
  alpha[8] = -0.8164965809277261*B1[1]*dv3; 
  alpha[11] = 2.828427124746191*(B2[2]*wv2+E0[2])-2.828427124746191*B1[2]*wv3; 
  alpha[21] = 0.8164965809277261*B2[2]*dv2; 
  alpha[25] = -0.8164965809277261*B1[2]*dv3; 
  alpha[31] = 2.828427124746191*(B2[3]*wv2+E0[3])-2.828427124746191*B1[3]*wv3; 
  const double amid = 0.25*alpha[0]-0.2795084971874737*alpha[11]; 
  Ghat[0] = (-1.322875655532295*fjump[32])+alpha[0]*(0.3307189138830738*favg[32]+0.2795084971874737*favg[12]+0.2165063509461096*favg[2]+0.125*favg[0])+0.125*alpha[31]*favg[31]+alpha[4]*(0.2795084971874737*favg[26]+0.2165063509461096*favg[9]+0.125*favg[4])+0.125*alpha[25]*favg[25]+alpha[3]*(0.2795084971874737*favg[22]+0.2165063509461096*favg[7]+0.125*favg[3])+0.125*alpha[21]*favg[21]+alpha[1]*(0.2795084971874737*favg[20]+0.2165063509461096*favg[5]+0.125*favg[1])+alpha[11]*(0.2165063509461096*favg[19]+0.125*favg[11])+alpha[8]*(0.2165063509461096*favg[16]+0.125*favg[8])+alpha[6]*(0.2165063509461096*favg[15]+0.125*favg[6])-1.118033988749895*fjump[12]-0.8660254037844386*fjump[2]-0.5*fjump[0]; 
  Ghat[1] = alpha[1]*(0.3307189138830738*favg[32]+0.1936491673103708*favg[19]+0.2795084971874737*favg[12]+0.1118033988749895*favg[11]+0.2165063509461096*favg[2]+0.125*favg[0])+alpha[11]*(0.10978875820671*favg[31]+0.25*favg[20]+0.1936491673103708*favg[5]+0.1118033988749895*favg[1])+(0.1901597073139162*favg[19]+0.10978875820671*favg[11])*alpha[31]+alpha[8]*(0.2795084971874737*favg[26]+0.1118033988749895*favg[25]+0.2165063509461096*favg[9]+0.125*favg[4])+(0.1936491673103708*favg[16]+0.1118033988749895*favg[8])*alpha[25]+alpha[6]*(0.2795084971874737*favg[22]+0.1118033988749895*favg[21]+0.2165063509461096*favg[7]+0.125*favg[3])+(0.1936491673103708*favg[15]+0.1118033988749895*favg[6])*alpha[21]-1.118033988749895*fjump[20]+alpha[0]*(0.2795084971874737*favg[20]+0.2165063509461096*favg[5]+0.125*favg[1])+alpha[4]*(0.2165063509461096*favg[16]+0.125*favg[8])+alpha[3]*(0.2165063509461096*favg[15]+0.125*favg[6])-0.8660254037844386*fjump[5]-0.5*fjump[1]; 
  Ghat[3] = alpha[3]*(0.3307189138830738*favg[32]+0.1936491673103708*favg[24]+0.1118033988749895*favg[13]+0.2795084971874737*favg[12]+0.2165063509461096*favg[2]+0.125*favg[0])+alpha[6]*(0.1118033988749895*favg[23]+0.2795084971874737*favg[20]+0.2165063509461096*favg[5]+0.125*favg[1])-1.118033988749895*fjump[22]+alpha[0]*(0.2795084971874737*favg[22]+0.2165063509461096*favg[7]+0.125*favg[3])+0.125*alpha[11]*favg[21]+(0.2165063509461096*favg[19]+0.125*favg[11])*alpha[21]+alpha[4]*(0.2165063509461096*favg[18]+0.125*favg[10])+0.125*alpha[8]*favg[17]+alpha[1]*(0.2165063509461096*favg[15]+0.125*favg[6])-0.8660254037844386*fjump[7]-0.5*fjump[3]; 
  Ghat[4] = alpha[4]*(0.3307189138830738*favg[32]+0.1936491673103708*favg[29]+0.1118033988749895*favg[14]+0.2795084971874737*favg[12]+0.2165063509461096*favg[2]+0.125*favg[0])+alpha[8]*(0.1118033988749895*favg[28]+0.2795084971874737*favg[20]+0.2165063509461096*favg[5]+0.125*favg[1])-1.118033988749895*fjump[26]+alpha[0]*(0.2795084971874737*favg[26]+0.2165063509461096*favg[9]+0.125*favg[4])+0.125*alpha[11]*favg[25]+(0.2165063509461096*favg[19]+0.125*favg[11])*alpha[25]+alpha[3]*(0.2165063509461096*favg[18]+0.125*favg[10])+0.125*alpha[6]*favg[17]+alpha[1]*(0.2165063509461096*favg[16]+0.125*favg[8])-0.8660254037844386*fjump[9]-0.5*fjump[4]; 
  Ghat[6] = alpha[6]*(0.3307189138830738*favg[32]+0.1936491673103708*(favg[24]+favg[19])+0.1118033988749895*favg[13]+0.2795084971874737*favg[12]+0.1118033988749895*favg[11]+0.2165063509461096*favg[2]+0.125*favg[0])+alpha[21]*(0.10978875820671*favg[31]+0.1*favg[23]+0.25*favg[20]+0.1936491673103708*favg[5]+0.1118033988749895*favg[1])+0.10978875820671*favg[21]*alpha[31]+0.1118033988749895*favg[17]*alpha[25]+alpha[3]*(0.1118033988749895*favg[23]+0.2795084971874737*favg[20]+0.2165063509461096*favg[5]+0.125*favg[1])+alpha[1]*(0.2795084971874737*favg[22]+0.1118033988749895*favg[21]+0.2165063509461096*favg[7]+0.125*favg[3])+alpha[8]*(0.2165063509461096*favg[18]+0.125*favg[10])+0.125*alpha[4]*favg[17]-0.8660254037844386*fjump[15]+alpha[0]*(0.2165063509461096*favg[15]+0.125*favg[6])+alpha[11]*(0.1936491673103708*favg[15]+0.1118033988749895*favg[6])-0.5*fjump[6]; 
  Ghat[8] = alpha[8]*(0.3307189138830738*favg[32]+0.1936491673103708*(favg[29]+favg[19])+0.1118033988749895*favg[14]+0.2795084971874737*favg[12]+0.1118033988749895*favg[11]+0.2165063509461096*favg[2]+0.125*favg[0])+alpha[25]*(0.10978875820671*favg[31]+0.1*favg[28]+0.25*favg[20]+0.1936491673103708*favg[5]+0.1118033988749895*favg[1])+0.10978875820671*favg[25]*alpha[31]+alpha[4]*(0.1118033988749895*favg[28]+0.2795084971874737*favg[20]+0.2165063509461096*favg[5]+0.125*favg[1])+alpha[1]*(0.2795084971874737*favg[26]+0.1118033988749895*favg[25]+0.2165063509461096*favg[9]+0.125*favg[4])+0.1118033988749895*favg[17]*alpha[21]+alpha[6]*(0.2165063509461096*favg[18]+0.125*favg[10])+0.125*alpha[3]*favg[17]-0.8660254037844386*fjump[16]+alpha[0]*(0.2165063509461096*favg[16]+0.125*favg[8])+alpha[11]*(0.1936491673103708*favg[16]+0.1118033988749895*favg[8])-0.5*fjump[8]; 
  Ghat[10] = alpha[4]*(0.1118033988749895*favg[30]+0.2795084971874737*favg[22]+0.2165063509461096*favg[7]+0.125*favg[3])+alpha[3]*(0.1118033988749895*favg[27]+0.2795084971874737*favg[26]+0.2165063509461096*favg[9]+0.125*favg[4])+0.125*(alpha[21]*favg[25]+favg[21]*alpha[25])-0.8660254037844386*fjump[18]+alpha[0]*(0.2165063509461096*favg[18]+0.125*favg[10])+0.125*alpha[1]*favg[17]+alpha[6]*(0.2165063509461096*favg[16]+0.125*favg[8])+alpha[8]*(0.2165063509461096*favg[15]+0.125*favg[6])-0.5*fjump[10]; 
  Ghat[11] = alpha[11]*(0.3307189138830738*favg[32]+0.138320833793122*favg[19]+0.2795084971874737*favg[12]+0.07985957062499249*favg[11]+0.2165063509461096*favg[2]+0.125*favg[0])+alpha[1]*(0.10978875820671*favg[31]+0.25*favg[20]+0.1936491673103708*favg[5]+0.1118033988749895*favg[1])+alpha[31]*(0.07453559924999298*favg[31]+0.2454951265154914*favg[20]+0.1901597073139162*favg[5]+0.10978875820671*favg[1])+alpha[25]*(0.2795084971874737*favg[26]+0.07985957062499249*favg[25]+0.2165063509461096*favg[9]+0.125*favg[4])+0.125*alpha[4]*favg[25]+alpha[21]*(0.2795084971874737*favg[22]+0.07985957062499249*favg[21]+0.2165063509461096*favg[7]+0.125*favg[3])+0.125*alpha[3]*favg[21]-0.8660254037844386*fjump[19]+alpha[0]*(0.2165063509461096*favg[19]+0.125*favg[11])+alpha[8]*(0.1936491673103708*favg[16]+0.1118033988749895*favg[8])+alpha[6]*(0.1936491673103708*favg[15]+0.1118033988749895*favg[6])-0.5*fjump[11]; 
  Ghat[13] = alpha[3]*(0.10978875820671*favg[33]+0.25*favg[22]+0.1936491673103708*favg[7]+0.1118033988749895*favg[3])+0.125*alpha[4]*favg[27]-0.8660254037844386*fjump[24]+alpha[0]*(0.2165063509461096*favg[24]+0.125*favg[13])+0.125*alpha[1]*favg[23]+0.1118033988749895*alpha[21]*favg[21]+alpha[6]*(0.1936491673103708*favg[15]+0.1118033988749895*favg[6])-0.5*fjump[13]; 
  Ghat[14] = alpha[4]*(0.10978875820671*favg[34]+0.25*favg[26]+0.1936491673103708*favg[9]+0.1118033988749895*favg[4])+0.125*alpha[3]*favg[30]-0.8660254037844386*fjump[29]+alpha[0]*(0.2165063509461096*favg[29]+0.125*favg[14])+0.125*alpha[1]*favg[28]+0.1118033988749895*alpha[25]*favg[25]+alpha[8]*(0.1936491673103708*favg[16]+0.1118033988749895*favg[8])-0.5*fjump[14]; 
  Ghat[17] = alpha[8]*(0.1118033988749895*favg[30]+0.2795084971874737*favg[22]+0.1118033988749895*favg[21]+0.2165063509461096*favg[7]+0.125*favg[3])+alpha[6]*(0.1118033988749895*favg[27]+0.2795084971874737*favg[26]+0.1118033988749895*favg[25]+0.2165063509461096*favg[9]+0.125*favg[4])+(0.1936491673103708*favg[15]+0.1118033988749895*favg[6])*alpha[25]+(0.1936491673103708*favg[16]+0.1118033988749895*favg[8])*alpha[21]+alpha[1]*(0.2165063509461096*favg[18]+0.125*favg[10])-0.5*fjump[17]+(0.1118033988749895*alpha[11]+0.125*alpha[0])*favg[17]+alpha[3]*(0.2165063509461096*favg[16]+0.125*favg[8])+alpha[4]*(0.2165063509461096*favg[15]+0.125*favg[6]); 
  Ghat[21] = alpha[21]*(0.3307189138830738*favg[32]+0.1936491673103708*favg[24]+0.138320833793122*favg[19]+0.1118033988749895*favg[13]+0.2795084971874737*favg[12]+0.07985957062499249*favg[11]+0.2165063509461096*favg[2]+0.125*favg[0])+alpha[6]*(0.10978875820671*favg[31]+0.1*favg[23]+0.25*favg[20]+0.1936491673103708*favg[5]+0.1118033988749895*favg[1])+(0.1901597073139162*favg[15]+0.10978875820671*favg[6])*alpha[31]+(0.2165063509461096*favg[18]+0.125*favg[10])*alpha[25]+alpha[11]*(0.2795084971874737*favg[22]+0.07985957062499249*favg[21]+0.2165063509461096*favg[7]+0.125*favg[3])-0.5*fjump[21]+0.125*alpha[0]*favg[21]+alpha[3]*(0.2165063509461096*favg[19]+0.125*favg[11])+0.1118033988749895*alpha[8]*favg[17]+alpha[1]*(0.1936491673103708*favg[15]+0.1118033988749895*favg[6]); 
  Ghat[23] = alpha[6]*(0.10978875820671*favg[33]+0.25*favg[22]+0.1*favg[21]+0.1936491673103708*favg[7]+0.1118033988749895*favg[3])+0.125*alpha[8]*favg[27]+alpha[1]*(0.2165063509461096*favg[24]+0.125*favg[13])-0.5*fjump[23]+(0.1118033988749895*alpha[11]+0.125*alpha[0])*favg[23]+(0.1732050807568877*favg[15]+0.1*favg[6])*alpha[21]+alpha[3]*(0.1936491673103708*favg[15]+0.1118033988749895*favg[6]); 
  Ghat[25] = alpha[25]*(0.3307189138830738*favg[32]+0.1936491673103708*favg[29]+0.138320833793122*favg[19]+0.1118033988749895*favg[14]+0.2795084971874737*favg[12]+0.07985957062499249*favg[11]+0.2165063509461096*favg[2]+0.125*favg[0])+alpha[8]*(0.10978875820671*favg[31]+0.1*favg[28]+0.25*favg[20]+0.1936491673103708*favg[5]+0.1118033988749895*favg[1])+(0.1901597073139162*favg[16]+0.10978875820671*favg[8])*alpha[31]+alpha[11]*(0.2795084971874737*favg[26]+0.07985957062499249*favg[25]+0.2165063509461096*favg[9]+0.125*favg[4])-0.5*fjump[25]+0.125*alpha[0]*favg[25]+(0.2165063509461096*favg[18]+0.125*favg[10])*alpha[21]+alpha[4]*(0.2165063509461096*favg[19]+0.125*favg[11])+0.1118033988749895*alpha[6]*favg[17]+alpha[1]*(0.1936491673103708*favg[16]+0.1118033988749895*favg[8]); 
  Ghat[27] = (-0.5*fjump[27])+0.125*alpha[0]*favg[27]+alpha[4]*(0.2165063509461096*favg[24]+0.125*favg[13])+0.125*alpha[8]*favg[23]+alpha[3]*(0.1936491673103708*favg[18]+0.1118033988749895*favg[10])+0.1118033988749895*alpha[6]*favg[17]; 
  Ghat[28] = alpha[8]*(0.10978875820671*favg[34]+0.25*favg[26]+0.1*favg[25]+0.1936491673103708*favg[9]+0.1118033988749895*favg[4])+0.125*alpha[6]*favg[30]+alpha[1]*(0.2165063509461096*favg[29]+0.125*favg[14])-0.5*fjump[28]+(0.1118033988749895*alpha[11]+0.125*alpha[0])*favg[28]+(0.1732050807568877*favg[16]+0.1*favg[8])*alpha[25]+alpha[4]*(0.1936491673103708*favg[16]+0.1118033988749895*favg[8]); 
  Ghat[30] = (-0.5*fjump[30])+0.125*alpha[0]*favg[30]+alpha[3]*(0.2165063509461096*favg[29]+0.125*favg[14])+0.125*alpha[6]*favg[28]+alpha[4]*(0.1936491673103708*favg[18]+0.1118033988749895*favg[10])+0.1118033988749895*alpha[8]*favg[17]; 
  Ghat[31] = alpha[31]*(0.3307189138830738*favg[32]+0.1290994448735806*favg[19]+0.2795084971874737*favg[12]+0.07453559924999298*favg[11]+0.2165063509461096*favg[2]+0.125*favg[0])-0.5*fjump[31]+0.125*alpha[0]*favg[31]+alpha[11]*(0.07453559924999298*favg[31]+0.2454951265154914*favg[20]+0.1901597073139162*favg[5]+0.10978875820671*favg[1])+0.10978875820671*alpha[8]*favg[25]+(0.1901597073139162*favg[16]+0.10978875820671*favg[8])*alpha[25]+0.10978875820671*alpha[6]*favg[21]+(0.1901597073139162*favg[15]+0.10978875820671*favg[6])*alpha[21]+alpha[1]*(0.1901597073139162*favg[19]+0.10978875820671*favg[11]); 
  Ghat[33] = (-0.5*fjump[33])+0.125*alpha[0]*favg[33]+alpha[3]*(0.1901597073139162*favg[24]+0.10978875820671*favg[13])+0.10978875820671*alpha[6]*favg[23]; 
  Ghat[34] = (-0.5*fjump[34])+0.125*alpha[0]*favg[34]+alpha[4]*(0.1901597073139162*favg[29]+0.10978875820671*favg[14])+0.10978875820671*alpha[8]*favg[28]; 

  outr[0] += 0.5*Ghat[0]*dv10r; 
  outr[1] += 0.5*Ghat[1]*dv10r; 
  outr[2] += -0.8660254037844386*Ghat[0]*dv10r; 
  outr[3] += 0.5*Ghat[3]*dv10r; 
  outr[4] += 0.5*Ghat[4]*dv10r; 
  outr[5] += -0.8660254037844386*Ghat[1]*dv10r; 
  outr[6] += 0.5*Ghat[6]*dv10r; 
  outr[7] += -0.8660254037844386*Ghat[3]*dv10r; 
  outr[8] += 0.5*Ghat[8]*dv10r; 
  outr[9] += -0.8660254037844386*Ghat[4]*dv10r; 
  outr[10] += 0.5*Ghat[10]*dv10r; 
  outr[11] += 0.5*Ghat[11]*dv10r; 
  outr[12] += 1.118033988749895*Ghat[0]*dv10r; 
  outr[13] += 0.5*Ghat[13]*dv10r; 
  outr[14] += 0.5*Ghat[14]*dv10r; 
  outr[15] += -0.8660254037844386*Ghat[6]*dv10r; 
  outr[16] += -0.8660254037844386*Ghat[8]*dv10r; 
  outr[17] += 0.5*Ghat[17]*dv10r; 
  outr[18] += -0.8660254037844386*Ghat[10]*dv10r; 
  outr[19] += -0.8660254037844387*Ghat[11]*dv10r; 
  outr[20] += 1.118033988749895*Ghat[1]*dv10r; 
  outr[21] += 0.5*Ghat[21]*dv10r; 
  outr[22] += 1.118033988749895*Ghat[3]*dv10r; 
  outr[23] += 0.5*Ghat[23]*dv10r; 
  outr[24] += -0.8660254037844387*Ghat[13]*dv10r; 
  outr[25] += 0.5*Ghat[25]*dv10r; 
  outr[26] += 1.118033988749895*Ghat[4]*dv10r; 
  outr[27] += 0.5*Ghat[27]*dv10r; 
  outr[28] += 0.5*Ghat[28]*dv10r; 
  outr[29] += -0.8660254037844387*Ghat[14]*dv10r; 
  outr[30] += 0.5*Ghat[30]*dv10r; 
  outr[31] += 0.5*Ghat[31]*dv10r; 
  outr[32] += -1.322875655532295*Ghat[0]*dv10r; 
  outr[33] += 0.5*Ghat[33]*dv10r; 
  outr[34] += 0.5*Ghat[34]*dv10r; 

  outl[0] += -0.5*Ghat[0]*dv10l; 
  outl[1] += -0.5*Ghat[1]*dv10l; 
  outl[2] += -0.8660254037844386*Ghat[0]*dv10l; 
  outl[3] += -0.5*Ghat[3]*dv10l; 
  outl[4] += -0.5*Ghat[4]*dv10l; 
  outl[5] += -0.8660254037844386*Ghat[1]*dv10l; 
  outl[6] += -0.5*Ghat[6]*dv10l; 
  outl[7] += -0.8660254037844386*Ghat[3]*dv10l; 
  outl[8] += -0.5*Ghat[8]*dv10l; 
  outl[9] += -0.8660254037844386*Ghat[4]*dv10l; 
  outl[10] += -0.5*Ghat[10]*dv10l; 
  outl[11] += -0.5*Ghat[11]*dv10l; 
  outl[12] += -1.118033988749895*Ghat[0]*dv10l; 
  outl[13] += -0.5*Ghat[13]*dv10l; 
  outl[14] += -0.5*Ghat[14]*dv10l; 
  outl[15] += -0.8660254037844386*Ghat[6]*dv10l; 
  outl[16] += -0.8660254037844386*Ghat[8]*dv10l; 
  outl[17] += -0.5*Ghat[17]*dv10l; 
  outl[18] += -0.8660254037844386*Ghat[10]*dv10l; 
  outl[19] += -0.8660254037844387*Ghat[11]*dv10l; 
  outl[20] += -1.118033988749895*Ghat[1]*dv10l; 
  outl[21] += -0.5*Ghat[21]*dv10l; 
  outl[22] += -1.118033988749895*Ghat[3]*dv10l; 
  outl[23] += -0.5*Ghat[23]*dv10l; 
  outl[24] += -0.8660254037844387*Ghat[13]*dv10l; 
  outl[25] += -0.5*Ghat[25]*dv10l; 
  outl[26] += -1.118033988749895*Ghat[4]*dv10l; 
  outl[27] += -0.5*Ghat[27]*dv10l; 
  outl[28] += -0.5*Ghat[28]*dv10l; 
  outl[29] += -0.8660254037844387*Ghat[14]*dv10l; 
  outl[30] += -0.5*Ghat[30]*dv10l; 
  outl[31] += -0.5*Ghat[31]*dv10l; 
  outl[32] += -1.322875655532295*Ghat[0]*dv10l; 
  outl[33] += -0.5*Ghat[33]*dv10l; 
  outl[34] += -0.5*Ghat[34]*dv10l; 
return std::abs(amid); 
} 
double VlasovSurfElcMag1x3vMax_VY_P1(const double *wl, const double *wr, const double *dxvl, const double *dxvr, const double amax, const double *EM, const double *fl, const double *fr, double *outl, double *outr) 
{ 
// w: Cell-center coordinates. dxv[NDIM]: Cell spacing. amax: amax in global lax flux. E: EM field. fl/fr: Distribution function in left/right cells 
// outl/outr: output distribution function in left/right cells 
// returns abs(amid) for use in determining amax in cfl and global lax flux 
  double dv11l = 2/dxvl[2]; 
  double dv11r = 2/dxvr[2]; 
  const double *E1 = &EM[2]; 

  const double dv1 = dxvr[1], wv1 = wr[1]; 
  const double dv2 = dxvr[2], wv2 = wr[2]; 
  const double dv3 = dxvr[3], wv3 = wr[3]; 

  const double *B0 = &EM[6]; 
  const double *B1 = &EM[8]; 
  const double *B2 = &EM[10]; 

  double Ghat[5]; 

  double alpha[5]; 

  double favg[5]; 

  favg[0] = 1*fr[0]+fl[0]; 
  favg[1] = 1*fr[1]+fl[1]; 
  favg[2] = 1*fr[2]+fl[2]; 
  favg[3] = -1*fr[3]+fl[3]; 
  favg[4] = 1*fr[4]+fl[4]; 
  double fjump[5]; 

  fjump[0] = amax*(1*fr[0]-fl[0]); 
  fjump[1] = amax*(1*fr[1]-fl[1]); 
  fjump[2] = amax*(1*fr[2]-fl[2]); 
  fjump[3] = amax*(-1*fr[3]-fl[3]); 
  fjump[4] = amax*(1*fr[4]-fl[4]); 
  alpha[0] = 2.828427124746191*B0[0]*wv3-2.828427124746191*B2[0]*wv1+2.828427124746191*E1[0]; 
  alpha[1] = 2.828427124746191*B0[1]*wv3-2.828427124746191*B2[1]*wv1+2.828427124746191*E1[1]; 
  alpha[2] = -0.8164965809277261*B2[0]*dv1; 
  alpha[4] = 0.8164965809277261*B0[0]*dv3; 
  const double amid = 0.25*alpha[0]; 
  Ghat[0] = 0.125*alpha[4]*favg[4]-0.8660254037844386*fjump[3]+alpha[0]*(0.2165063509461096*favg[3]+0.125*favg[0])+0.125*(alpha[2]*favg[2]+alpha[1]*favg[1])-0.5*fjump[0]; 
  Ghat[1] = alpha[1]*(0.2165063509461096*favg[3]+0.125*favg[0])-0.5*fjump[1]+0.125*alpha[0]*favg[1]; 
  Ghat[2] = alpha[2]*(0.2165063509461096*favg[3]+0.125*favg[0])-0.5*fjump[2]+0.125*alpha[0]*favg[2]; 
  Ghat[4] = (-0.5*fjump[4])+0.125*alpha[0]*favg[4]+(0.2165063509461096*favg[3]+0.125*favg[0])*alpha[4]; 

  outr[0] += 0.5*Ghat[0]*dv11r; 
  outr[1] += 0.5*Ghat[1]*dv11r; 
  outr[2] += 0.5*Ghat[2]*dv11r; 
  outr[3] += -0.8660254037844386*Ghat[0]*dv11r; 
  outr[4] += 0.5*Ghat[4]*dv11r; 

  outl[0] += -0.5*Ghat[0]*dv11l; 
  outl[1] += -0.5*Ghat[1]*dv11l; 
  outl[2] += -0.5*Ghat[2]*dv11l; 
  outl[3] += -0.8660254037844386*Ghat[0]*dv11l; 
  outl[4] += -0.5*Ghat[4]*dv11l; 
return std::abs(amid); 
} 
double VlasovSurfElcMag1x3vMax_VY_P2(const double *wl, const double *wr, const double *dxvl, const double *dxvr, const double amax, const double *EM, const double *fl, const double *fr, double *outl, double *outr) 
{ 
// w: Cell-center coordinates. dxv[NDIM]: Cell spacing. amax: amax in global lax flux. E: EM field. fl/fr: Distribution function in left/right cells 
// outl/outr: output distribution function in left/right cells 
// returns abs(amid) for use in determining amax in cfl and global lax flux 
  double dv11l = 2/dxvl[2]; 
  double dv11r = 2/dxvr[2]; 
  const double *E1 = &EM[3]; 

  const double dv1 = dxvr[1], wv1 = wr[1]; 
  const double dv2 = dxvr[2], wv2 = wr[2]; 
  const double dv3 = dxvr[3], wv3 = wr[3]; 

  const double *B0 = &EM[9]; 
  const double *B1 = &EM[12]; 
  const double *B2 = &EM[15]; 

  double Ghat[15]; 

  double alpha[15]; 

  double favg[15]; 

  favg[0] = 1*fr[0]+fl[0]; 
  favg[1] = 1*fr[1]+fl[1]; 
  favg[2] = 1*fr[2]+fl[2]; 
  favg[3] = -1*fr[3]+fl[3]; 
  favg[4] = 1*fr[4]+fl[4]; 
  favg[5] = 1*fr[5]+fl[5]; 
  favg[6] = -1*fr[6]+fl[6]; 
  favg[7] = -1*fr[7]+fl[7]; 
  favg[8] = 1*fr[8]+fl[8]; 
  favg[9] = 1*fr[9]+fl[9]; 
  favg[10] = -1*fr[10]+fl[10]; 
  favg[11] = 1*fr[11]+fl[11]; 
  favg[12] = 1*fr[12]+fl[12]; 
  favg[13] = 1*fr[13]+fl[13]; 
  favg[14] = 1*fr[14]+fl[14]; 
  double fjump[15]; 

  fjump[0] = amax*(1*fr[0]-fl[0]); 
  fjump[1] = amax*(1*fr[1]-fl[1]); 
  fjump[2] = amax*(1*fr[2]-fl[2]); 
  fjump[3] = amax*(-1*fr[3]-fl[3]); 
  fjump[4] = amax*(1*fr[4]-fl[4]); 
  fjump[5] = amax*(1*fr[5]-fl[5]); 
  fjump[6] = amax*(-1*fr[6]-fl[6]); 
  fjump[7] = amax*(-1*fr[7]-fl[7]); 
  fjump[8] = amax*(1*fr[8]-fl[8]); 
  fjump[9] = amax*(1*fr[9]-fl[9]); 
  fjump[10] = amax*(-1*fr[10]-fl[10]); 
  fjump[11] = amax*(1*fr[11]-fl[11]); 
  fjump[12] = amax*(1*fr[12]-fl[12]); 
  fjump[13] = amax*(1*fr[13]-fl[13]); 
  fjump[14] = amax*(1*fr[14]-fl[14]); 
  alpha[0] = 2.828427124746191*B0[0]*wv3-2.828427124746191*B2[0]*wv1+2.828427124746191*E1[0]; 
  alpha[1] = 2.828427124746191*B0[1]*wv3-2.828427124746191*B2[1]*wv1+2.828427124746191*E1[1]; 
  alpha[2] = -0.8164965809277261*B2[0]*dv1; 
  alpha[4] = 0.8164965809277261*B0[0]*dv3; 
  alpha[5] = -0.8164965809277261*B2[1]*dv1; 
  alpha[8] = 0.8164965809277261*B0[1]*dv3; 
  alpha[11] = 2.828427124746191*B0[2]*wv3-2.828427124746191*B2[2]*wv1+2.828427124746191*E1[2]; 
  const double amid = 0.25*alpha[0]-0.2795084971874737*alpha[11]; 
  Ghat[0] = (-1.118033988749895*fjump[13])+alpha[0]*(0.2795084971874737*favg[13]+0.2165063509461096*favg[3]+0.125*favg[0])+0.125*alpha[11]*favg[11]+alpha[4]*(0.2165063509461096*favg[10]+0.125*favg[4])+0.125*alpha[8]*favg[8]+alpha[2]*(0.2165063509461096*favg[7]+0.125*favg[2])+alpha[1]*(0.2165063509461096*favg[6]+0.125*favg[1])+0.125*alpha[5]*favg[5]-0.8660254037844386*fjump[3]-0.5*fjump[0]; 
  Ghat[1] = alpha[1]*(0.2795084971874737*favg[13]+0.1118033988749895*favg[11]+0.2165063509461096*favg[3]+0.125*favg[0])+(0.1936491673103708*favg[6]+0.1118033988749895*favg[1])*alpha[11]+alpha[8]*(0.2165063509461096*favg[10]+0.125*favg[4])+0.125*alpha[4]*favg[8]+alpha[5]*(0.2165063509461096*favg[7]+0.125*favg[2])-0.8660254037844386*fjump[6]+alpha[0]*(0.2165063509461096*favg[6]+0.125*favg[1])+0.125*alpha[2]*favg[5]-0.5*fjump[1]; 
  Ghat[2] = alpha[2]*(0.2795084971874737*favg[13]+0.1118033988749895*favg[12]+0.2165063509461096*favg[3]+0.125*favg[0])+0.125*alpha[4]*favg[9]-0.8660254037844386*fjump[7]+alpha[0]*(0.2165063509461096*favg[7]+0.125*favg[2])+alpha[5]*(0.2165063509461096*favg[6]+0.125*favg[1])+0.125*alpha[1]*favg[5]-0.5*fjump[2]; 
  Ghat[4] = alpha[4]*(0.1118033988749895*favg[14]+0.2795084971874737*favg[13]+0.2165063509461096*favg[3]+0.125*favg[0])-0.8660254037844386*fjump[10]+alpha[0]*(0.2165063509461096*favg[10]+0.125*favg[4])+0.125*(alpha[2]*favg[9]+alpha[1]*favg[8])+(0.2165063509461096*favg[6]+0.125*favg[1])*alpha[8]-0.5*fjump[4]; 
  Ghat[5] = alpha[5]*(0.2795084971874737*favg[13]+0.1118033988749895*(favg[12]+favg[11])+0.2165063509461096*favg[3]+0.125*favg[0])+0.1118033988749895*favg[5]*alpha[11]+0.125*alpha[8]*favg[9]+alpha[1]*(0.2165063509461096*favg[7]+0.125*favg[2])+alpha[2]*(0.2165063509461096*favg[6]+0.125*favg[1])-0.5*fjump[5]+0.125*alpha[0]*favg[5]; 
  Ghat[8] = alpha[8]*(0.1118033988749895*favg[14]+0.2795084971874737*favg[13]+0.1118033988749895*favg[11]+0.2165063509461096*favg[3]+0.125*favg[0])+0.1118033988749895*favg[8]*alpha[11]+alpha[1]*(0.2165063509461096*favg[10]+0.125*favg[4])+0.125*alpha[5]*favg[9]-0.5*fjump[8]+0.125*alpha[0]*favg[8]+alpha[4]*(0.2165063509461096*favg[6]+0.125*favg[1]); 
  Ghat[9] = alpha[2]*(0.2165063509461096*favg[10]+0.125*favg[4])-0.5*fjump[9]+0.125*(alpha[0]*favg[9]+alpha[5]*favg[8]+favg[5]*alpha[8])+alpha[4]*(0.2165063509461096*favg[7]+0.125*favg[2]); 
  Ghat[11] = alpha[11]*(0.2795084971874737*favg[13]+0.07985957062499249*favg[11]+0.2165063509461096*favg[3]+0.125*favg[0])-0.5*fjump[11]+0.125*alpha[0]*favg[11]+0.1118033988749895*alpha[8]*favg[8]+alpha[1]*(0.1936491673103708*favg[6]+0.1118033988749895*favg[1])+0.1118033988749895*alpha[5]*favg[5]; 
  Ghat[12] = (-0.5*fjump[12])+0.125*alpha[0]*favg[12]+alpha[2]*(0.1936491673103708*favg[7]+0.1118033988749895*favg[2])+0.1118033988749895*alpha[5]*favg[5]; 
  Ghat[14] = (-0.5*fjump[14])+0.125*alpha[0]*favg[14]+alpha[4]*(0.1936491673103708*favg[10]+0.1118033988749895*favg[4])+0.1118033988749895*alpha[8]*favg[8]; 

  outr[0] += 0.5*Ghat[0]*dv11r; 
  outr[1] += 0.5*Ghat[1]*dv11r; 
  outr[2] += 0.5*Ghat[2]*dv11r; 
  outr[3] += -0.8660254037844386*Ghat[0]*dv11r; 
  outr[4] += 0.5*Ghat[4]*dv11r; 
  outr[5] += 0.5*Ghat[5]*dv11r; 
  outr[6] += -0.8660254037844386*Ghat[1]*dv11r; 
  outr[7] += -0.8660254037844386*Ghat[2]*dv11r; 
  outr[8] += 0.5*Ghat[8]*dv11r; 
  outr[9] += 0.5*Ghat[9]*dv11r; 
  outr[10] += -0.8660254037844386*Ghat[4]*dv11r; 
  outr[11] += 0.5*Ghat[11]*dv11r; 
  outr[12] += 0.5*Ghat[12]*dv11r; 
  outr[13] += 1.118033988749895*Ghat[0]*dv11r; 
  outr[14] += 0.5*Ghat[14]*dv11r; 

  outl[0] += -0.5*Ghat[0]*dv11l; 
  outl[1] += -0.5*Ghat[1]*dv11l; 
  outl[2] += -0.5*Ghat[2]*dv11l; 
  outl[3] += -0.8660254037844386*Ghat[0]*dv11l; 
  outl[4] += -0.5*Ghat[4]*dv11l; 
  outl[5] += -0.5*Ghat[5]*dv11l; 
  outl[6] += -0.8660254037844386*Ghat[1]*dv11l; 
  outl[7] += -0.8660254037844386*Ghat[2]*dv11l; 
  outl[8] += -0.5*Ghat[8]*dv11l; 
  outl[9] += -0.5*Ghat[9]*dv11l; 
  outl[10] += -0.8660254037844386*Ghat[4]*dv11l; 
  outl[11] += -0.5*Ghat[11]*dv11l; 
  outl[12] += -0.5*Ghat[12]*dv11l; 
  outl[13] += -1.118033988749895*Ghat[0]*dv11l; 
  outl[14] += -0.5*Ghat[14]*dv11l; 
return std::abs(amid); 
} 
double VlasovSurfElcMag1x3vMax_VY_P3(const double *wl, const double *wr, const double *dxvl, const double *dxvr, const double amax, const double *EM, const double *fl, const double *fr, double *outl, double *outr) 
{ 
// w: Cell-center coordinates. dxv[NDIM]: Cell spacing. amax: amax in global lax flux. E: EM field. fl/fr: Distribution function in left/right cells 
// outl/outr: output distribution function in left/right cells 
// returns abs(amid) for use in determining amax in cfl and global lax flux 
  double dv11l = 2/dxvl[2]; 
  double dv11r = 2/dxvr[2]; 
  const double *E1 = &EM[4]; 

  const double dv1 = dxvr[1], wv1 = wr[1]; 
  const double dv2 = dxvr[2], wv2 = wr[2]; 
  const double dv3 = dxvr[3], wv3 = wr[3]; 

  const double *B0 = &EM[12]; 
  const double *B1 = &EM[16]; 
  const double *B2 = &EM[20]; 

  double Ghat[35]; 

  double alpha[35]; 

  double favg[35]; 

  favg[0] = 1*fr[0]+fl[0]; 
  favg[1] = 1*fr[1]+fl[1]; 
  favg[2] = 1*fr[2]+fl[2]; 
  favg[3] = -1*fr[3]+fl[3]; 
  favg[4] = 1*fr[4]+fl[4]; 
  favg[5] = 1*fr[5]+fl[5]; 
  favg[6] = -1*fr[6]+fl[6]; 
  favg[7] = -1*fr[7]+fl[7]; 
  favg[8] = 1*fr[8]+fl[8]; 
  favg[9] = 1*fr[9]+fl[9]; 
  favg[10] = -1*fr[10]+fl[10]; 
  favg[11] = 1*fr[11]+fl[11]; 
  favg[12] = 1*fr[12]+fl[12]; 
  favg[13] = 1*fr[13]+fl[13]; 
  favg[14] = 1*fr[14]+fl[14]; 
  favg[15] = -1*fr[15]+fl[15]; 
  favg[16] = 1*fr[16]+fl[16]; 
  favg[17] = -1*fr[17]+fl[17]; 
  favg[18] = -1*fr[18]+fl[18]; 
  favg[19] = 1*fr[19]+fl[19]; 
  favg[20] = 1*fr[20]+fl[20]; 
  favg[21] = -1*fr[21]+fl[21]; 
  favg[22] = -1*fr[22]+fl[22]; 
  favg[23] = 1*fr[23]+fl[23]; 
  favg[24] = 1*fr[24]+fl[24]; 
  favg[25] = 1*fr[25]+fl[25]; 
  favg[26] = 1*fr[26]+fl[26]; 
  favg[27] = 1*fr[27]+fl[27]; 
  favg[28] = 1*fr[28]+fl[28]; 
  favg[29] = 1*fr[29]+fl[29]; 
  favg[30] = -1*fr[30]+fl[30]; 
  favg[31] = 1*fr[31]+fl[31]; 
  favg[32] = 1*fr[32]+fl[32]; 
  favg[33] = -1*fr[33]+fl[33]; 
  favg[34] = 1*fr[34]+fl[34]; 
  double fjump[35]; 

  fjump[0] = amax*(1*fr[0]-fl[0]); 
  fjump[1] = amax*(1*fr[1]-fl[1]); 
  fjump[2] = amax*(1*fr[2]-fl[2]); 
  fjump[3] = amax*(-1*fr[3]-fl[3]); 
  fjump[4] = amax*(1*fr[4]-fl[4]); 
  fjump[5] = amax*(1*fr[5]-fl[5]); 
  fjump[6] = amax*(-1*fr[6]-fl[6]); 
  fjump[7] = amax*(-1*fr[7]-fl[7]); 
  fjump[8] = amax*(1*fr[8]-fl[8]); 
  fjump[9] = amax*(1*fr[9]-fl[9]); 
  fjump[10] = amax*(-1*fr[10]-fl[10]); 
  fjump[11] = amax*(1*fr[11]-fl[11]); 
  fjump[12] = amax*(1*fr[12]-fl[12]); 
  fjump[13] = amax*(1*fr[13]-fl[13]); 
  fjump[14] = amax*(1*fr[14]-fl[14]); 
  fjump[15] = amax*(-1*fr[15]-fl[15]); 
  fjump[16] = amax*(1*fr[16]-fl[16]); 
  fjump[17] = amax*(-1*fr[17]-fl[17]); 
  fjump[18] = amax*(-1*fr[18]-fl[18]); 
  fjump[19] = amax*(1*fr[19]-fl[19]); 
  fjump[20] = amax*(1*fr[20]-fl[20]); 
  fjump[21] = amax*(-1*fr[21]-fl[21]); 
  fjump[22] = amax*(-1*fr[22]-fl[22]); 
  fjump[23] = amax*(1*fr[23]-fl[23]); 
  fjump[24] = amax*(1*fr[24]-fl[24]); 
  fjump[25] = amax*(1*fr[25]-fl[25]); 
  fjump[26] = amax*(1*fr[26]-fl[26]); 
  fjump[27] = amax*(1*fr[27]-fl[27]); 
  fjump[28] = amax*(1*fr[28]-fl[28]); 
  fjump[29] = amax*(1*fr[29]-fl[29]); 
  fjump[30] = amax*(-1*fr[30]-fl[30]); 
  fjump[31] = amax*(1*fr[31]-fl[31]); 
  fjump[32] = amax*(1*fr[32]-fl[32]); 
  fjump[33] = amax*(-1*fr[33]-fl[33]); 
  fjump[34] = amax*(1*fr[34]-fl[34]); 
  alpha[0] = 2.828427124746191*B0[0]*wv3-2.828427124746191*B2[0]*wv1+2.828427124746191*E1[0]; 
  alpha[1] = 2.828427124746191*B0[1]*wv3-2.828427124746191*B2[1]*wv1+2.828427124746191*E1[1]; 
  alpha[2] = -0.8164965809277261*B2[0]*dv1; 
  alpha[4] = 0.8164965809277261*B0[0]*dv3; 
  alpha[5] = -0.8164965809277261*B2[1]*dv1; 
  alpha[8] = 0.8164965809277261*B0[1]*dv3; 
  alpha[11] = 2.828427124746191*B0[2]*wv3-2.828427124746191*B2[2]*wv1+2.828427124746191*E1[2]; 
  alpha[19] = -0.8164965809277261*B2[2]*dv1; 
  alpha[25] = 0.8164965809277261*B0[2]*dv3; 
  alpha[31] = 2.828427124746191*B0[3]*wv3-2.828427124746191*B2[3]*wv1+2.828427124746191*E1[3]; 
  const double amid = 0.25*alpha[0]-0.2795084971874737*alpha[11]; 
  Ghat[0] = (-1.322875655532295*fjump[33])+alpha[0]*(0.3307189138830738*favg[33]+0.2795084971874737*favg[13]+0.2165063509461096*favg[3]+0.125*favg[0])+0.125*alpha[31]*favg[31]+alpha[4]*(0.2795084971874737*favg[27]+0.2165063509461096*favg[10]+0.125*favg[4])+0.125*alpha[25]*favg[25]+alpha[2]*(0.2795084971874737*favg[24]+0.2165063509461096*favg[7]+0.125*favg[2])+alpha[1]*(0.2795084971874737*favg[23]+0.2165063509461096*favg[6]+0.125*favg[1])+alpha[11]*(0.2165063509461096*favg[21]+0.125*favg[11])+0.125*alpha[19]*favg[19]+alpha[8]*(0.2165063509461096*favg[17]+0.125*favg[8])+alpha[5]*(0.2165063509461096*favg[15]+0.125*favg[5])-1.118033988749895*fjump[13]-0.8660254037844386*fjump[3]-0.5*fjump[0]; 
  Ghat[1] = alpha[1]*(0.3307189138830738*favg[33]+0.1936491673103708*favg[21]+0.2795084971874737*favg[13]+0.1118033988749895*favg[11]+0.2165063509461096*favg[3]+0.125*favg[0])+alpha[11]*(0.10978875820671*favg[31]+0.25*favg[23]+0.1936491673103708*favg[6]+0.1118033988749895*favg[1])+(0.1901597073139162*favg[21]+0.10978875820671*favg[11])*alpha[31]+alpha[8]*(0.2795084971874737*favg[27]+0.1118033988749895*favg[25]+0.2165063509461096*favg[10]+0.125*favg[4])+(0.1936491673103708*favg[17]+0.1118033988749895*favg[8])*alpha[25]+alpha[5]*(0.2795084971874737*favg[24]+0.1118033988749895*favg[19]+0.2165063509461096*favg[7]+0.125*favg[2])-1.118033988749895*fjump[23]+alpha[0]*(0.2795084971874737*favg[23]+0.2165063509461096*favg[6]+0.125*favg[1])+(0.1936491673103708*favg[15]+0.1118033988749895*favg[5])*alpha[19]+alpha[4]*(0.2165063509461096*favg[17]+0.125*favg[8])+alpha[2]*(0.2165063509461096*favg[15]+0.125*favg[5])-0.8660254037844386*fjump[6]-0.5*fjump[1]; 
  Ghat[2] = alpha[2]*(0.3307189138830738*favg[33]+0.1936491673103708*favg[22]+0.2795084971874737*favg[13]+0.1118033988749895*favg[12]+0.2165063509461096*favg[3]+0.125*favg[0])-1.118033988749895*fjump[24]+alpha[0]*(0.2795084971874737*favg[24]+0.2165063509461096*favg[7]+0.125*favg[2])+alpha[5]*(0.2795084971874737*favg[23]+0.1118033988749895*favg[20]+0.2165063509461096*favg[6]+0.125*favg[1])+alpha[19]*(0.2165063509461096*favg[21]+0.125*favg[11])+0.125*alpha[11]*favg[19]+alpha[4]*(0.2165063509461096*favg[18]+0.125*favg[9])+0.125*alpha[8]*favg[16]+alpha[1]*(0.2165063509461096*favg[15]+0.125*favg[5])-0.8660254037844386*fjump[7]-0.5*fjump[2]; 
  Ghat[4] = alpha[4]*(0.3307189138830738*favg[33]+0.1936491673103708*favg[30]+0.1118033988749895*favg[14]+0.2795084971874737*favg[13]+0.2165063509461096*favg[3]+0.125*favg[0])+alpha[8]*(0.1118033988749895*favg[28]+0.2795084971874737*favg[23]+0.2165063509461096*favg[6]+0.125*favg[1])-1.118033988749895*fjump[27]+alpha[0]*(0.2795084971874737*favg[27]+0.2165063509461096*favg[10]+0.125*favg[4])+0.125*alpha[11]*favg[25]+(0.2165063509461096*favg[21]+0.125*favg[11])*alpha[25]+alpha[2]*(0.2165063509461096*favg[18]+0.125*favg[9])+alpha[1]*(0.2165063509461096*favg[17]+0.125*favg[8])+0.125*alpha[5]*favg[16]-0.8660254037844386*fjump[10]-0.5*fjump[4]; 
  Ghat[5] = alpha[5]*(0.3307189138830738*favg[33]+0.1936491673103708*(favg[22]+favg[21])+0.2795084971874737*favg[13]+0.1118033988749895*(favg[12]+favg[11])+0.2165063509461096*favg[3]+0.125*favg[0])+alpha[19]*(0.10978875820671*favg[31]+0.25*favg[23]+0.1*favg[20]+0.1936491673103708*favg[6]+0.1118033988749895*favg[1])+0.10978875820671*favg[19]*alpha[31]+0.1118033988749895*favg[16]*alpha[25]+alpha[1]*(0.2795084971874737*favg[24]+0.1118033988749895*favg[19]+0.2165063509461096*favg[7]+0.125*favg[2])+alpha[2]*(0.2795084971874737*favg[23]+0.1118033988749895*favg[20]+0.2165063509461096*favg[6]+0.125*favg[1])+alpha[8]*(0.2165063509461096*favg[18]+0.125*favg[9])+0.125*alpha[4]*favg[16]-0.8660254037844386*fjump[15]+alpha[0]*(0.2165063509461096*favg[15]+0.125*favg[5])+alpha[11]*(0.1936491673103708*favg[15]+0.1118033988749895*favg[5])-0.5*fjump[5]; 
  Ghat[8] = alpha[8]*(0.3307189138830738*favg[33]+0.1936491673103708*(favg[30]+favg[21])+0.1118033988749895*favg[14]+0.2795084971874737*favg[13]+0.1118033988749895*favg[11]+0.2165063509461096*favg[3]+0.125*favg[0])+alpha[25]*(0.10978875820671*favg[31]+0.1*favg[28]+0.25*favg[23]+0.1936491673103708*favg[6]+0.1118033988749895*favg[1])+0.10978875820671*favg[25]*alpha[31]+alpha[4]*(0.1118033988749895*favg[28]+0.2795084971874737*favg[23]+0.2165063509461096*favg[6]+0.125*favg[1])+alpha[1]*(0.2795084971874737*favg[27]+0.1118033988749895*favg[25]+0.2165063509461096*favg[10]+0.125*favg[4])+0.1118033988749895*favg[16]*alpha[19]+alpha[5]*(0.2165063509461096*favg[18]+0.125*favg[9])-0.8660254037844386*fjump[17]+alpha[0]*(0.2165063509461096*favg[17]+0.125*favg[8])+alpha[11]*(0.1936491673103708*favg[17]+0.1118033988749895*favg[8])+0.125*alpha[2]*favg[16]-0.5*fjump[8]; 
  Ghat[9] = alpha[4]*(0.1118033988749895*favg[29]+0.2795084971874737*favg[24]+0.2165063509461096*favg[7]+0.125*favg[2])+alpha[2]*(0.2795084971874737*favg[27]+0.1118033988749895*favg[26]+0.2165063509461096*favg[10]+0.125*favg[4])+0.125*(alpha[19]*favg[25]+favg[19]*alpha[25])-0.8660254037844386*fjump[18]+alpha[0]*(0.2165063509461096*favg[18]+0.125*favg[9])+alpha[5]*(0.2165063509461096*favg[17]+0.125*favg[8])+0.125*alpha[1]*favg[16]+alpha[8]*(0.2165063509461096*favg[15]+0.125*favg[5])-0.5*fjump[9]; 
  Ghat[11] = alpha[11]*(0.3307189138830738*favg[33]+0.138320833793122*favg[21]+0.2795084971874737*favg[13]+0.07985957062499249*favg[11]+0.2165063509461096*favg[3]+0.125*favg[0])+alpha[1]*(0.10978875820671*favg[31]+0.25*favg[23]+0.1936491673103708*favg[6]+0.1118033988749895*favg[1])+alpha[31]*(0.07453559924999298*favg[31]+0.2454951265154914*favg[23]+0.1901597073139162*favg[6]+0.10978875820671*favg[1])+alpha[25]*(0.2795084971874737*favg[27]+0.07985957062499249*favg[25]+0.2165063509461096*favg[10]+0.125*favg[4])+0.125*alpha[4]*favg[25]+alpha[19]*(0.2795084971874737*favg[24]+0.07985957062499249*favg[19]+0.2165063509461096*favg[7]+0.125*favg[2])-0.8660254037844386*fjump[21]+alpha[0]*(0.2165063509461096*favg[21]+0.125*favg[11])+0.125*alpha[2]*favg[19]+alpha[8]*(0.1936491673103708*favg[17]+0.1118033988749895*favg[8])+alpha[5]*(0.1936491673103708*favg[15]+0.1118033988749895*favg[5])-0.5*fjump[11]; 
  Ghat[12] = alpha[2]*(0.10978875820671*favg[32]+0.25*favg[24]+0.1936491673103708*favg[7]+0.1118033988749895*favg[2])+0.125*alpha[4]*favg[26]-0.8660254037844386*fjump[22]+alpha[0]*(0.2165063509461096*favg[22]+0.125*favg[12])+0.125*alpha[1]*favg[20]+0.1118033988749895*alpha[19]*favg[19]+alpha[5]*(0.1936491673103708*favg[15]+0.1118033988749895*favg[5])-0.5*fjump[12]; 
  Ghat[14] = alpha[4]*(0.10978875820671*favg[34]+0.25*favg[27]+0.1936491673103708*favg[10]+0.1118033988749895*favg[4])-0.8660254037844386*fjump[30]+alpha[0]*(0.2165063509461096*favg[30]+0.125*favg[14])+0.125*(alpha[2]*favg[29]+alpha[1]*favg[28])+0.1118033988749895*alpha[25]*favg[25]+alpha[8]*(0.1936491673103708*favg[17]+0.1118033988749895*favg[8])-0.5*fjump[14]; 
  Ghat[16] = alpha[8]*(0.1118033988749895*favg[29]+0.2795084971874737*favg[24]+0.1118033988749895*favg[19]+0.2165063509461096*favg[7]+0.125*favg[2])+alpha[5]*(0.2795084971874737*favg[27]+0.1118033988749895*(favg[26]+favg[25])+0.2165063509461096*favg[10]+0.125*favg[4])+(0.1936491673103708*favg[15]+0.1118033988749895*favg[5])*alpha[25]+(0.1936491673103708*favg[17]+0.1118033988749895*favg[8])*alpha[19]+alpha[1]*(0.2165063509461096*favg[18]+0.125*favg[9])+alpha[2]*(0.2165063509461096*favg[17]+0.125*favg[8])-0.5*fjump[16]+(0.1118033988749895*alpha[11]+0.125*alpha[0])*favg[16]+alpha[4]*(0.2165063509461096*favg[15]+0.125*favg[5]); 
  Ghat[19] = alpha[19]*(0.3307189138830738*favg[33]+0.1936491673103708*favg[22]+0.138320833793122*favg[21]+0.2795084971874737*favg[13]+0.1118033988749895*favg[12]+0.07985957062499249*favg[11]+0.2165063509461096*favg[3]+0.125*favg[0])+alpha[5]*(0.10978875820671*favg[31]+0.25*favg[23]+0.1*favg[20]+0.1936491673103708*favg[6]+0.1118033988749895*favg[1])+(0.1901597073139162*favg[15]+0.10978875820671*favg[5])*alpha[31]+(0.2165063509461096*favg[18]+0.125*favg[9])*alpha[25]+alpha[11]*(0.2795084971874737*favg[24]+0.07985957062499249*favg[19]+0.2165063509461096*favg[7]+0.125*favg[2])+alpha[2]*(0.2165063509461096*favg[21]+0.125*favg[11])-0.5*fjump[19]+0.125*alpha[0]*favg[19]+0.1118033988749895*alpha[8]*favg[16]+alpha[1]*(0.1936491673103708*favg[15]+0.1118033988749895*favg[5]); 
  Ghat[20] = alpha[5]*(0.10978875820671*favg[32]+0.25*favg[24]+0.1*favg[19]+0.1936491673103708*favg[7]+0.1118033988749895*favg[2])+0.125*alpha[8]*favg[26]+alpha[1]*(0.2165063509461096*favg[22]+0.125*favg[12])-0.5*fjump[20]+(0.1118033988749895*alpha[11]+0.125*alpha[0])*favg[20]+(0.1732050807568877*favg[15]+0.1*favg[5])*alpha[19]+alpha[2]*(0.1936491673103708*favg[15]+0.1118033988749895*favg[5]); 
  Ghat[25] = alpha[25]*(0.3307189138830738*favg[33]+0.1936491673103708*favg[30]+0.138320833793122*favg[21]+0.1118033988749895*favg[14]+0.2795084971874737*favg[13]+0.07985957062499249*favg[11]+0.2165063509461096*favg[3]+0.125*favg[0])+alpha[8]*(0.10978875820671*favg[31]+0.1*favg[28]+0.25*favg[23]+0.1936491673103708*favg[6]+0.1118033988749895*favg[1])+(0.1901597073139162*favg[17]+0.10978875820671*favg[8])*alpha[31]+alpha[11]*(0.2795084971874737*favg[27]+0.07985957062499249*favg[25]+0.2165063509461096*favg[10]+0.125*favg[4])-0.5*fjump[25]+0.125*alpha[0]*favg[25]+alpha[4]*(0.2165063509461096*favg[21]+0.125*favg[11])+(0.2165063509461096*favg[18]+0.125*favg[9])*alpha[19]+alpha[1]*(0.1936491673103708*favg[17]+0.1118033988749895*favg[8])+0.1118033988749895*alpha[5]*favg[16]; 
  Ghat[26] = (-0.5*fjump[26])+0.125*alpha[0]*favg[26]+alpha[4]*(0.2165063509461096*favg[22]+0.125*favg[12])+0.125*alpha[8]*favg[20]+alpha[2]*(0.1936491673103708*favg[18]+0.1118033988749895*favg[9])+0.1118033988749895*alpha[5]*favg[16]; 
  Ghat[28] = alpha[8]*(0.10978875820671*favg[34]+0.25*favg[27]+0.1*favg[25]+0.1936491673103708*favg[10]+0.1118033988749895*favg[4])+alpha[1]*(0.2165063509461096*favg[30]+0.125*favg[14])+0.125*alpha[5]*favg[29]-0.5*fjump[28]+(0.1118033988749895*alpha[11]+0.125*alpha[0])*favg[28]+(0.1732050807568877*favg[17]+0.1*favg[8])*alpha[25]+alpha[4]*(0.1936491673103708*favg[17]+0.1118033988749895*favg[8]); 
  Ghat[29] = alpha[2]*(0.2165063509461096*favg[30]+0.125*favg[14])-0.5*fjump[29]+0.125*(alpha[0]*favg[29]+alpha[5]*favg[28])+alpha[4]*(0.1936491673103708*favg[18]+0.1118033988749895*favg[9])+0.1118033988749895*alpha[8]*favg[16]; 
  Ghat[31] = alpha[31]*(0.3307189138830738*favg[33]+0.1290994448735806*favg[21]+0.2795084971874737*favg[13]+0.07453559924999298*favg[11]+0.2165063509461096*favg[3]+0.125*favg[0])-0.5*fjump[31]+0.125*alpha[0]*favg[31]+alpha[11]*(0.07453559924999298*favg[31]+0.2454951265154914*favg[23]+0.1901597073139162*favg[6]+0.10978875820671*favg[1])+0.10978875820671*alpha[8]*favg[25]+(0.1901597073139162*favg[17]+0.10978875820671*favg[8])*alpha[25]+alpha[1]*(0.1901597073139162*favg[21]+0.10978875820671*favg[11])+0.10978875820671*alpha[5]*favg[19]+(0.1901597073139162*favg[15]+0.10978875820671*favg[5])*alpha[19]; 
  Ghat[32] = (-0.5*fjump[32])+0.125*alpha[0]*favg[32]+alpha[2]*(0.1901597073139162*favg[22]+0.10978875820671*favg[12])+0.10978875820671*alpha[5]*favg[20]; 
  Ghat[34] = (-0.5*fjump[34])+0.125*alpha[0]*favg[34]+alpha[4]*(0.1901597073139162*favg[30]+0.10978875820671*favg[14])+0.10978875820671*alpha[8]*favg[28]; 

  outr[0] += 0.5*Ghat[0]*dv11r; 
  outr[1] += 0.5*Ghat[1]*dv11r; 
  outr[2] += 0.5*Ghat[2]*dv11r; 
  outr[3] += -0.8660254037844386*Ghat[0]*dv11r; 
  outr[4] += 0.5*Ghat[4]*dv11r; 
  outr[5] += 0.5*Ghat[5]*dv11r; 
  outr[6] += -0.8660254037844386*Ghat[1]*dv11r; 
  outr[7] += -0.8660254037844386*Ghat[2]*dv11r; 
  outr[8] += 0.5*Ghat[8]*dv11r; 
  outr[9] += 0.5*Ghat[9]*dv11r; 
  outr[10] += -0.8660254037844386*Ghat[4]*dv11r; 
  outr[11] += 0.5*Ghat[11]*dv11r; 
  outr[12] += 0.5*Ghat[12]*dv11r; 
  outr[13] += 1.118033988749895*Ghat[0]*dv11r; 
  outr[14] += 0.5*Ghat[14]*dv11r; 
  outr[15] += -0.8660254037844386*Ghat[5]*dv11r; 
  outr[16] += 0.5*Ghat[16]*dv11r; 
  outr[17] += -0.8660254037844386*Ghat[8]*dv11r; 
  outr[18] += -0.8660254037844386*Ghat[9]*dv11r; 
  outr[19] += 0.5*Ghat[19]*dv11r; 
  outr[20] += 0.5*Ghat[20]*dv11r; 
  outr[21] += -0.8660254037844387*Ghat[11]*dv11r; 
  outr[22] += -0.8660254037844387*Ghat[12]*dv11r; 
  outr[23] += 1.118033988749895*Ghat[1]*dv11r; 
  outr[24] += 1.118033988749895*Ghat[2]*dv11r; 
  outr[25] += 0.5*Ghat[25]*dv11r; 
  outr[26] += 0.5*Ghat[26]*dv11r; 
  outr[27] += 1.118033988749895*Ghat[4]*dv11r; 
  outr[28] += 0.5*Ghat[28]*dv11r; 
  outr[29] += 0.5*Ghat[29]*dv11r; 
  outr[30] += -0.8660254037844387*Ghat[14]*dv11r; 
  outr[31] += 0.5*Ghat[31]*dv11r; 
  outr[32] += 0.5*Ghat[32]*dv11r; 
  outr[33] += -1.322875655532295*Ghat[0]*dv11r; 
  outr[34] += 0.5*Ghat[34]*dv11r; 

  outl[0] += -0.5*Ghat[0]*dv11l; 
  outl[1] += -0.5*Ghat[1]*dv11l; 
  outl[2] += -0.5*Ghat[2]*dv11l; 
  outl[3] += -0.8660254037844386*Ghat[0]*dv11l; 
  outl[4] += -0.5*Ghat[4]*dv11l; 
  outl[5] += -0.5*Ghat[5]*dv11l; 
  outl[6] += -0.8660254037844386*Ghat[1]*dv11l; 
  outl[7] += -0.8660254037844386*Ghat[2]*dv11l; 
  outl[8] += -0.5*Ghat[8]*dv11l; 
  outl[9] += -0.5*Ghat[9]*dv11l; 
  outl[10] += -0.8660254037844386*Ghat[4]*dv11l; 
  outl[11] += -0.5*Ghat[11]*dv11l; 
  outl[12] += -0.5*Ghat[12]*dv11l; 
  outl[13] += -1.118033988749895*Ghat[0]*dv11l; 
  outl[14] += -0.5*Ghat[14]*dv11l; 
  outl[15] += -0.8660254037844386*Ghat[5]*dv11l; 
  outl[16] += -0.5*Ghat[16]*dv11l; 
  outl[17] += -0.8660254037844386*Ghat[8]*dv11l; 
  outl[18] += -0.8660254037844386*Ghat[9]*dv11l; 
  outl[19] += -0.5*Ghat[19]*dv11l; 
  outl[20] += -0.5*Ghat[20]*dv11l; 
  outl[21] += -0.8660254037844387*Ghat[11]*dv11l; 
  outl[22] += -0.8660254037844387*Ghat[12]*dv11l; 
  outl[23] += -1.118033988749895*Ghat[1]*dv11l; 
  outl[24] += -1.118033988749895*Ghat[2]*dv11l; 
  outl[25] += -0.5*Ghat[25]*dv11l; 
  outl[26] += -0.5*Ghat[26]*dv11l; 
  outl[27] += -1.118033988749895*Ghat[4]*dv11l; 
  outl[28] += -0.5*Ghat[28]*dv11l; 
  outl[29] += -0.5*Ghat[29]*dv11l; 
  outl[30] += -0.8660254037844387*Ghat[14]*dv11l; 
  outl[31] += -0.5*Ghat[31]*dv11l; 
  outl[32] += -0.5*Ghat[32]*dv11l; 
  outl[33] += -1.322875655532295*Ghat[0]*dv11l; 
  outl[34] += -0.5*Ghat[34]*dv11l; 
return std::abs(amid); 
} 
double VlasovSurfElcMag1x3vMax_VZ_P1(const double *wl, const double *wr, const double *dxvl, const double *dxvr, const double amax, const double *EM, const double *fl, const double *fr, double *outl, double *outr) 
{ 
// w: Cell-center coordinates. dxv[NDIM]: Cell spacing. amax: amax in global lax flux. E: EM field. fl/fr: Distribution function in left/right cells 
// outl/outr: output distribution function in left/right cells 
// returns abs(amid) for use in determining amax in cfl and global lax flux 
  double dv12l = 2/dxvl[3]; 
  double dv12r = 2/dxvr[3]; 
  const double *E2 = &EM[4]; 

  const double dv1 = dxvr[1], wv1 = wr[1]; 
  const double dv2 = dxvr[2], wv2 = wr[2]; 
  const double dv3 = dxvr[3], wv3 = wr[3]; 

  const double *B0 = &EM[6]; 
  const double *B1 = &EM[8]; 
  const double *B2 = &EM[10]; 

  double Ghat[5]; 

  double alpha[5]; 

  double favg[5]; 

  favg[0] = 1*fr[0]+fl[0]; 
  favg[1] = 1*fr[1]+fl[1]; 
  favg[2] = 1*fr[2]+fl[2]; 
  favg[3] = 1*fr[3]+fl[3]; 
  favg[4] = -1*fr[4]+fl[4]; 
  double fjump[5]; 

  fjump[0] = amax*(1*fr[0]-fl[0]); 
  fjump[1] = amax*(1*fr[1]-fl[1]); 
  fjump[2] = amax*(1*fr[2]-fl[2]); 
  fjump[3] = amax*(1*fr[3]-fl[3]); 
  fjump[4] = amax*(-1*fr[4]-fl[4]); 
  alpha[0] = 2.828427124746191*(B1[0]*wv1+E2[0])-2.828427124746191*B0[0]*wv2; 
  alpha[1] = 2.828427124746191*(B1[1]*wv1+E2[1])-2.828427124746191*B0[1]*wv2; 
  alpha[2] = 0.8164965809277261*B1[0]*dv1; 
  alpha[3] = -0.8164965809277261*B0[0]*dv2; 
  const double amid = 0.25*alpha[0]; 
  Ghat[0] = (-0.8660254037844386*fjump[4])+alpha[0]*(0.2165063509461096*favg[4]+0.125*favg[0])+0.125*(alpha[3]*favg[3]+alpha[2]*favg[2]+alpha[1]*favg[1])-0.5*fjump[0]; 
  Ghat[1] = alpha[1]*(0.2165063509461096*favg[4]+0.125*favg[0])-0.5*fjump[1]+0.125*alpha[0]*favg[1]; 
  Ghat[2] = alpha[2]*(0.2165063509461096*favg[4]+0.125*favg[0])-0.5*fjump[2]+0.125*alpha[0]*favg[2]; 
  Ghat[3] = alpha[3]*(0.2165063509461096*favg[4]+0.125*favg[0])-0.5*fjump[3]+0.125*alpha[0]*favg[3]; 

  outr[0] += 0.5*Ghat[0]*dv12r; 
  outr[1] += 0.5*Ghat[1]*dv12r; 
  outr[2] += 0.5*Ghat[2]*dv12r; 
  outr[3] += 0.5*Ghat[3]*dv12r; 
  outr[4] += -0.8660254037844386*Ghat[0]*dv12r; 

  outl[0] += -0.5*Ghat[0]*dv12l; 
  outl[1] += -0.5*Ghat[1]*dv12l; 
  outl[2] += -0.5*Ghat[2]*dv12l; 
  outl[3] += -0.5*Ghat[3]*dv12l; 
  outl[4] += -0.8660254037844386*Ghat[0]*dv12l; 
return std::abs(amid); 
} 
double VlasovSurfElcMag1x3vMax_VZ_P2(const double *wl, const double *wr, const double *dxvl, const double *dxvr, const double amax, const double *EM, const double *fl, const double *fr, double *outl, double *outr) 
{ 
// w: Cell-center coordinates. dxv[NDIM]: Cell spacing. amax: amax in global lax flux. E: EM field. fl/fr: Distribution function in left/right cells 
// outl/outr: output distribution function in left/right cells 
// returns abs(amid) for use in determining amax in cfl and global lax flux 
  double dv12l = 2/dxvl[3]; 
  double dv12r = 2/dxvr[3]; 
  const double *E2 = &EM[6]; 

  const double dv1 = dxvr[1], wv1 = wr[1]; 
  const double dv2 = dxvr[2], wv2 = wr[2]; 
  const double dv3 = dxvr[3], wv3 = wr[3]; 

  const double *B0 = &EM[9]; 
  const double *B1 = &EM[12]; 
  const double *B2 = &EM[15]; 

  double Ghat[15]; 

  double alpha[15]; 

  double favg[15]; 

  favg[0] = 1*fr[0]+fl[0]; 
  favg[1] = 1*fr[1]+fl[1]; 
  favg[2] = 1*fr[2]+fl[2]; 
  favg[3] = 1*fr[3]+fl[3]; 
  favg[4] = -1*fr[4]+fl[4]; 
  favg[5] = 1*fr[5]+fl[5]; 
  favg[6] = 1*fr[6]+fl[6]; 
  favg[7] = 1*fr[7]+fl[7]; 
  favg[8] = -1*fr[8]+fl[8]; 
  favg[9] = -1*fr[9]+fl[9]; 
  favg[10] = -1*fr[10]+fl[10]; 
  favg[11] = 1*fr[11]+fl[11]; 
  favg[12] = 1*fr[12]+fl[12]; 
  favg[13] = 1*fr[13]+fl[13]; 
  favg[14] = 1*fr[14]+fl[14]; 
  double fjump[15]; 

  fjump[0] = amax*(1*fr[0]-fl[0]); 
  fjump[1] = amax*(1*fr[1]-fl[1]); 
  fjump[2] = amax*(1*fr[2]-fl[2]); 
  fjump[3] = amax*(1*fr[3]-fl[3]); 
  fjump[4] = amax*(-1*fr[4]-fl[4]); 
  fjump[5] = amax*(1*fr[5]-fl[5]); 
  fjump[6] = amax*(1*fr[6]-fl[6]); 
  fjump[7] = amax*(1*fr[7]-fl[7]); 
  fjump[8] = amax*(-1*fr[8]-fl[8]); 
  fjump[9] = amax*(-1*fr[9]-fl[9]); 
  fjump[10] = amax*(-1*fr[10]-fl[10]); 
  fjump[11] = amax*(1*fr[11]-fl[11]); 
  fjump[12] = amax*(1*fr[12]-fl[12]); 
  fjump[13] = amax*(1*fr[13]-fl[13]); 
  fjump[14] = amax*(1*fr[14]-fl[14]); 
  alpha[0] = 2.828427124746191*(B1[0]*wv1+E2[0])-2.828427124746191*B0[0]*wv2; 
  alpha[1] = 2.828427124746191*(B1[1]*wv1+E2[1])-2.828427124746191*B0[1]*wv2; 
  alpha[2] = 0.8164965809277261*B1[0]*dv1; 
  alpha[3] = -0.8164965809277261*B0[0]*dv2; 
  alpha[5] = 0.8164965809277261*B1[1]*dv1; 
  alpha[6] = -0.8164965809277261*B0[1]*dv2; 
  alpha[11] = 2.828427124746191*(B1[2]*wv1+E2[2])-2.828427124746191*B0[2]*wv2; 
  const double amid = 0.25*alpha[0]-0.2795084971874737*alpha[11]; 
  Ghat[0] = (-1.118033988749895*fjump[14])+alpha[0]*(0.2795084971874737*favg[14]+0.2165063509461096*favg[4]+0.125*favg[0])+0.125*alpha[11]*favg[11]+alpha[3]*(0.2165063509461096*favg[10]+0.125*favg[3])+alpha[2]*(0.2165063509461096*favg[9]+0.125*favg[2])+alpha[1]*(0.2165063509461096*favg[8]+0.125*favg[1])+0.125*(alpha[6]*favg[6]+alpha[5]*favg[5])-0.8660254037844386*fjump[4]-0.5*fjump[0]; 
  Ghat[1] = alpha[1]*(0.2795084971874737*favg[14]+0.1118033988749895*favg[11]+0.2165063509461096*favg[4]+0.125*favg[0])+(0.1936491673103708*favg[8]+0.1118033988749895*favg[1])*alpha[11]+alpha[6]*(0.2165063509461096*favg[10]+0.125*favg[3])+alpha[5]*(0.2165063509461096*favg[9]+0.125*favg[2])-0.8660254037844386*fjump[8]+alpha[0]*(0.2165063509461096*favg[8]+0.125*favg[1])+0.125*(alpha[3]*favg[6]+alpha[2]*favg[5])-0.5*fjump[1]; 
  Ghat[2] = alpha[2]*(0.2795084971874737*favg[14]+0.1118033988749895*favg[12]+0.2165063509461096*favg[4]+0.125*favg[0])-0.8660254037844386*fjump[9]+alpha[0]*(0.2165063509461096*favg[9]+0.125*favg[2])+alpha[5]*(0.2165063509461096*favg[8]+0.125*favg[1])+0.125*(alpha[3]*favg[7]+alpha[1]*favg[5])-0.5*fjump[2]; 
  Ghat[3] = alpha[3]*(0.2795084971874737*favg[14]+0.1118033988749895*favg[13]+0.2165063509461096*favg[4]+0.125*favg[0])-0.8660254037844386*fjump[10]+alpha[0]*(0.2165063509461096*favg[10]+0.125*favg[3])+alpha[6]*(0.2165063509461096*favg[8]+0.125*favg[1])+0.125*(alpha[2]*favg[7]+alpha[1]*favg[6])-0.5*fjump[3]; 
  Ghat[5] = alpha[5]*(0.2795084971874737*favg[14]+0.1118033988749895*(favg[12]+favg[11])+0.2165063509461096*favg[4]+0.125*favg[0])+0.1118033988749895*favg[5]*alpha[11]+alpha[1]*(0.2165063509461096*favg[9]+0.125*favg[2])+alpha[2]*(0.2165063509461096*favg[8]+0.125*favg[1])+0.125*alpha[6]*favg[7]-0.5*fjump[5]+0.125*alpha[0]*favg[5]; 
  Ghat[6] = alpha[6]*(0.2795084971874737*favg[14]+0.1118033988749895*(favg[13]+favg[11])+0.2165063509461096*favg[4]+0.125*favg[0])+0.1118033988749895*favg[6]*alpha[11]+alpha[1]*(0.2165063509461096*favg[10]+0.125*favg[3])+alpha[3]*(0.2165063509461096*favg[8]+0.125*favg[1])+0.125*alpha[5]*favg[7]-0.5*fjump[6]+0.125*alpha[0]*favg[6]; 
  Ghat[7] = alpha[2]*(0.2165063509461096*favg[10]+0.125*favg[3])+alpha[3]*(0.2165063509461096*favg[9]+0.125*favg[2])-0.5*fjump[7]+0.125*(alpha[0]*favg[7]+alpha[5]*favg[6]+favg[5]*alpha[6]); 
  Ghat[11] = alpha[11]*(0.2795084971874737*favg[14]+0.07985957062499249*favg[11]+0.2165063509461096*favg[4]+0.125*favg[0])-0.5*fjump[11]+0.125*alpha[0]*favg[11]+alpha[1]*(0.1936491673103708*favg[8]+0.1118033988749895*favg[1])+0.1118033988749895*(alpha[6]*favg[6]+alpha[5]*favg[5]); 
  Ghat[12] = (-0.5*fjump[12])+0.125*alpha[0]*favg[12]+alpha[2]*(0.1936491673103708*favg[9]+0.1118033988749895*favg[2])+0.1118033988749895*alpha[5]*favg[5]; 
  Ghat[13] = (-0.5*fjump[13])+0.125*alpha[0]*favg[13]+alpha[3]*(0.1936491673103708*favg[10]+0.1118033988749895*favg[3])+0.1118033988749895*alpha[6]*favg[6]; 

  outr[0] += 0.5*Ghat[0]*dv12r; 
  outr[1] += 0.5*Ghat[1]*dv12r; 
  outr[2] += 0.5*Ghat[2]*dv12r; 
  outr[3] += 0.5*Ghat[3]*dv12r; 
  outr[4] += -0.8660254037844386*Ghat[0]*dv12r; 
  outr[5] += 0.5*Ghat[5]*dv12r; 
  outr[6] += 0.5*Ghat[6]*dv12r; 
  outr[7] += 0.5*Ghat[7]*dv12r; 
  outr[8] += -0.8660254037844386*Ghat[1]*dv12r; 
  outr[9] += -0.8660254037844386*Ghat[2]*dv12r; 
  outr[10] += -0.8660254037844386*Ghat[3]*dv12r; 
  outr[11] += 0.5*Ghat[11]*dv12r; 
  outr[12] += 0.5*Ghat[12]*dv12r; 
  outr[13] += 0.5*Ghat[13]*dv12r; 
  outr[14] += 1.118033988749895*Ghat[0]*dv12r; 

  outl[0] += -0.5*Ghat[0]*dv12l; 
  outl[1] += -0.5*Ghat[1]*dv12l; 
  outl[2] += -0.5*Ghat[2]*dv12l; 
  outl[3] += -0.5*Ghat[3]*dv12l; 
  outl[4] += -0.8660254037844386*Ghat[0]*dv12l; 
  outl[5] += -0.5*Ghat[5]*dv12l; 
  outl[6] += -0.5*Ghat[6]*dv12l; 
  outl[7] += -0.5*Ghat[7]*dv12l; 
  outl[8] += -0.8660254037844386*Ghat[1]*dv12l; 
  outl[9] += -0.8660254037844386*Ghat[2]*dv12l; 
  outl[10] += -0.8660254037844386*Ghat[3]*dv12l; 
  outl[11] += -0.5*Ghat[11]*dv12l; 
  outl[12] += -0.5*Ghat[12]*dv12l; 
  outl[13] += -0.5*Ghat[13]*dv12l; 
  outl[14] += -1.118033988749895*Ghat[0]*dv12l; 
return std::abs(amid); 
} 
double VlasovSurfElcMag1x3vMax_VZ_P3(const double *wl, const double *wr, const double *dxvl, const double *dxvr, const double amax, const double *EM, const double *fl, const double *fr, double *outl, double *outr) 
{ 
// w: Cell-center coordinates. dxv[NDIM]: Cell spacing. amax: amax in global lax flux. E: EM field. fl/fr: Distribution function in left/right cells 
// outl/outr: output distribution function in left/right cells 
// returns abs(amid) for use in determining amax in cfl and global lax flux 
  double dv12l = 2/dxvl[3]; 
  double dv12r = 2/dxvr[3]; 
  const double *E2 = &EM[8]; 

  const double dv1 = dxvr[1], wv1 = wr[1]; 
  const double dv2 = dxvr[2], wv2 = wr[2]; 
  const double dv3 = dxvr[3], wv3 = wr[3]; 

  const double *B0 = &EM[12]; 
  const double *B1 = &EM[16]; 
  const double *B2 = &EM[20]; 

  double Ghat[35]; 

  double alpha[35]; 

  double favg[35]; 

  favg[0] = 1*fr[0]+fl[0]; 
  favg[1] = 1*fr[1]+fl[1]; 
  favg[2] = 1*fr[2]+fl[2]; 
  favg[3] = 1*fr[3]+fl[3]; 
  favg[4] = -1*fr[4]+fl[4]; 
  favg[5] = 1*fr[5]+fl[5]; 
  favg[6] = 1*fr[6]+fl[6]; 
  favg[7] = 1*fr[7]+fl[7]; 
  favg[8] = -1*fr[8]+fl[8]; 
  favg[9] = -1*fr[9]+fl[9]; 
  favg[10] = -1*fr[10]+fl[10]; 
  favg[11] = 1*fr[11]+fl[11]; 
  favg[12] = 1*fr[12]+fl[12]; 
  favg[13] = 1*fr[13]+fl[13]; 
  favg[14] = 1*fr[14]+fl[14]; 
  favg[15] = 1*fr[15]+fl[15]; 
  favg[16] = -1*fr[16]+fl[16]; 
  favg[17] = -1*fr[17]+fl[17]; 
  favg[18] = -1*fr[18]+fl[18]; 
  favg[19] = 1*fr[19]+fl[19]; 
  favg[20] = 1*fr[20]+fl[20]; 
  favg[21] = 1*fr[21]+fl[21]; 
  favg[22] = 1*fr[22]+fl[22]; 
  favg[23] = 1*fr[23]+fl[23]; 
  favg[24] = 1*fr[24]+fl[24]; 
  favg[25] = -1*fr[25]+fl[25]; 
  favg[26] = -1*fr[26]+fl[26]; 
  favg[27] = -1*fr[27]+fl[27]; 
  favg[28] = 1*fr[28]+fl[28]; 
  favg[29] = 1*fr[29]+fl[29]; 
  favg[30] = 1*fr[30]+fl[30]; 
  favg[31] = 1*fr[31]+fl[31]; 
  favg[32] = 1*fr[32]+fl[32]; 
  favg[33] = 1*fr[33]+fl[33]; 
  favg[34] = -1*fr[34]+fl[34]; 
  double fjump[35]; 

  fjump[0] = amax*(1*fr[0]-fl[0]); 
  fjump[1] = amax*(1*fr[1]-fl[1]); 
  fjump[2] = amax*(1*fr[2]-fl[2]); 
  fjump[3] = amax*(1*fr[3]-fl[3]); 
  fjump[4] = amax*(-1*fr[4]-fl[4]); 
  fjump[5] = amax*(1*fr[5]-fl[5]); 
  fjump[6] = amax*(1*fr[6]-fl[6]); 
  fjump[7] = amax*(1*fr[7]-fl[7]); 
  fjump[8] = amax*(-1*fr[8]-fl[8]); 
  fjump[9] = amax*(-1*fr[9]-fl[9]); 
  fjump[10] = amax*(-1*fr[10]-fl[10]); 
  fjump[11] = amax*(1*fr[11]-fl[11]); 
  fjump[12] = amax*(1*fr[12]-fl[12]); 
  fjump[13] = amax*(1*fr[13]-fl[13]); 
  fjump[14] = amax*(1*fr[14]-fl[14]); 
  fjump[15] = amax*(1*fr[15]-fl[15]); 
  fjump[16] = amax*(-1*fr[16]-fl[16]); 
  fjump[17] = amax*(-1*fr[17]-fl[17]); 
  fjump[18] = amax*(-1*fr[18]-fl[18]); 
  fjump[19] = amax*(1*fr[19]-fl[19]); 
  fjump[20] = amax*(1*fr[20]-fl[20]); 
  fjump[21] = amax*(1*fr[21]-fl[21]); 
  fjump[22] = amax*(1*fr[22]-fl[22]); 
  fjump[23] = amax*(1*fr[23]-fl[23]); 
  fjump[24] = amax*(1*fr[24]-fl[24]); 
  fjump[25] = amax*(-1*fr[25]-fl[25]); 
  fjump[26] = amax*(-1*fr[26]-fl[26]); 
  fjump[27] = amax*(-1*fr[27]-fl[27]); 
  fjump[28] = amax*(1*fr[28]-fl[28]); 
  fjump[29] = amax*(1*fr[29]-fl[29]); 
  fjump[30] = amax*(1*fr[30]-fl[30]); 
  fjump[31] = amax*(1*fr[31]-fl[31]); 
  fjump[32] = amax*(1*fr[32]-fl[32]); 
  fjump[33] = amax*(1*fr[33]-fl[33]); 
  fjump[34] = amax*(-1*fr[34]-fl[34]); 
  alpha[0] = 2.828427124746191*(B1[0]*wv1+E2[0])-2.828427124746191*B0[0]*wv2; 
  alpha[1] = 2.828427124746191*(B1[1]*wv1+E2[1])-2.828427124746191*B0[1]*wv2; 
  alpha[2] = 0.8164965809277261*B1[0]*dv1; 
  alpha[3] = -0.8164965809277261*B0[0]*dv2; 
  alpha[5] = 0.8164965809277261*B1[1]*dv1; 
  alpha[6] = -0.8164965809277261*B0[1]*dv2; 
  alpha[11] = 2.828427124746191*(B1[2]*wv1+E2[2])-2.828427124746191*B0[2]*wv2; 
  alpha[19] = 0.8164965809277261*B1[2]*dv1; 
  alpha[21] = -0.8164965809277261*B0[2]*dv2; 
  alpha[31] = 2.828427124746191*(B1[3]*wv1+E2[3])-2.828427124746191*B0[3]*wv2; 
  const double amid = 0.25*alpha[0]-0.2795084971874737*alpha[11]; 
  Ghat[0] = (-1.322875655532295*fjump[34])+alpha[0]*(0.3307189138830738*favg[34]+0.2795084971874737*favg[14]+0.2165063509461096*favg[4]+0.125*favg[0])+0.125*alpha[31]*favg[31]+alpha[3]*(0.2795084971874737*favg[30]+0.2165063509461096*favg[10]+0.125*favg[3])+alpha[2]*(0.2795084971874737*favg[29]+0.2165063509461096*favg[9]+0.125*favg[2])+alpha[1]*(0.2795084971874737*favg[28]+0.2165063509461096*favg[8]+0.125*favg[1])+alpha[11]*(0.2165063509461096*favg[25]+0.125*favg[11])+0.125*(alpha[21]*favg[21]+alpha[19]*favg[19])+alpha[6]*(0.2165063509461096*favg[17]+0.125*favg[6])+alpha[5]*(0.2165063509461096*favg[16]+0.125*favg[5])-1.118033988749895*fjump[14]-0.8660254037844386*fjump[4]-0.5*fjump[0]; 
  Ghat[1] = alpha[1]*(0.3307189138830738*favg[34]+0.1936491673103708*favg[25]+0.2795084971874737*favg[14]+0.1118033988749895*favg[11]+0.2165063509461096*favg[4]+0.125*favg[0])+alpha[11]*(0.10978875820671*favg[31]+0.25*favg[28]+0.1936491673103708*favg[8]+0.1118033988749895*favg[1])+(0.1901597073139162*favg[25]+0.10978875820671*favg[11])*alpha[31]+alpha[6]*(0.2795084971874737*favg[30]+0.1118033988749895*favg[21]+0.2165063509461096*favg[10]+0.125*favg[3])+alpha[5]*(0.2795084971874737*favg[29]+0.1118033988749895*favg[19]+0.2165063509461096*favg[9]+0.125*favg[2])-1.118033988749895*fjump[28]+alpha[0]*(0.2795084971874737*favg[28]+0.2165063509461096*favg[8]+0.125*favg[1])+(0.1936491673103708*favg[17]+0.1118033988749895*favg[6])*alpha[21]+(0.1936491673103708*favg[16]+0.1118033988749895*favg[5])*alpha[19]+alpha[3]*(0.2165063509461096*favg[17]+0.125*favg[6])+alpha[2]*(0.2165063509461096*favg[16]+0.125*favg[5])-0.8660254037844386*fjump[8]-0.5*fjump[1]; 
  Ghat[2] = alpha[2]*(0.3307189138830738*favg[34]+0.1936491673103708*favg[26]+0.2795084971874737*favg[14]+0.1118033988749895*favg[12]+0.2165063509461096*favg[4]+0.125*favg[0])-1.118033988749895*fjump[29]+alpha[0]*(0.2795084971874737*favg[29]+0.2165063509461096*favg[9]+0.125*favg[2])+alpha[5]*(0.2795084971874737*favg[28]+0.1118033988749895*favg[20]+0.2165063509461096*favg[8]+0.125*favg[1])+alpha[19]*(0.2165063509461096*favg[25]+0.125*favg[11])+0.125*alpha[11]*favg[19]+alpha[3]*(0.2165063509461096*favg[18]+0.125*favg[7])+alpha[1]*(0.2165063509461096*favg[16]+0.125*favg[5])+0.125*alpha[6]*favg[15]-0.8660254037844386*fjump[9]-0.5*fjump[2]; 
  Ghat[3] = alpha[3]*(0.3307189138830738*favg[34]+0.1936491673103708*favg[27]+0.2795084971874737*favg[14]+0.1118033988749895*favg[13]+0.2165063509461096*favg[4]+0.125*favg[0])-1.118033988749895*fjump[30]+alpha[0]*(0.2795084971874737*favg[30]+0.2165063509461096*favg[10]+0.125*favg[3])+alpha[6]*(0.2795084971874737*favg[28]+0.1118033988749895*favg[23]+0.2165063509461096*favg[8]+0.125*favg[1])+alpha[21]*(0.2165063509461096*favg[25]+0.125*favg[11])+0.125*alpha[11]*favg[21]+alpha[2]*(0.2165063509461096*favg[18]+0.125*favg[7])+alpha[1]*(0.2165063509461096*favg[17]+0.125*favg[6])+0.125*alpha[5]*favg[15]-0.8660254037844386*fjump[10]-0.5*fjump[3]; 
  Ghat[5] = alpha[5]*(0.3307189138830738*favg[34]+0.1936491673103708*(favg[26]+favg[25])+0.2795084971874737*favg[14]+0.1118033988749895*(favg[12]+favg[11])+0.2165063509461096*favg[4]+0.125*favg[0])+alpha[19]*(0.10978875820671*favg[31]+0.25*favg[28]+0.1*favg[20]+0.1936491673103708*favg[8]+0.1118033988749895*favg[1])+0.10978875820671*favg[19]*alpha[31]+alpha[1]*(0.2795084971874737*favg[29]+0.1118033988749895*favg[19]+0.2165063509461096*favg[9]+0.125*favg[2])+alpha[2]*(0.2795084971874737*favg[28]+0.1118033988749895*favg[20]+0.2165063509461096*favg[8]+0.125*favg[1])+0.1118033988749895*favg[15]*alpha[21]+alpha[6]*(0.2165063509461096*favg[18]+0.125*favg[7])-0.8660254037844386*fjump[16]+alpha[0]*(0.2165063509461096*favg[16]+0.125*favg[5])+alpha[11]*(0.1936491673103708*favg[16]+0.1118033988749895*favg[5])+0.125*alpha[3]*favg[15]-0.5*fjump[5]; 
  Ghat[6] = alpha[6]*(0.3307189138830738*favg[34]+0.1936491673103708*(favg[27]+favg[25])+0.2795084971874737*favg[14]+0.1118033988749895*(favg[13]+favg[11])+0.2165063509461096*favg[4]+0.125*favg[0])+alpha[21]*(0.10978875820671*favg[31]+0.25*favg[28]+0.1*favg[23]+0.1936491673103708*favg[8]+0.1118033988749895*favg[1])+0.10978875820671*favg[21]*alpha[31]+alpha[1]*(0.2795084971874737*favg[30]+0.1118033988749895*favg[21]+0.2165063509461096*favg[10]+0.125*favg[3])+alpha[3]*(0.2795084971874737*favg[28]+0.1118033988749895*favg[23]+0.2165063509461096*favg[8]+0.125*favg[1])+0.1118033988749895*favg[15]*alpha[19]+alpha[5]*(0.2165063509461096*favg[18]+0.125*favg[7])-0.8660254037844386*fjump[17]+alpha[0]*(0.2165063509461096*favg[17]+0.125*favg[6])+alpha[11]*(0.1936491673103708*favg[17]+0.1118033988749895*favg[6])+0.125*alpha[2]*favg[15]-0.5*fjump[6]; 
  Ghat[7] = alpha[2]*(0.2795084971874737*favg[30]+0.1118033988749895*favg[22]+0.2165063509461096*favg[10]+0.125*favg[3])+alpha[3]*(0.2795084971874737*favg[29]+0.1118033988749895*favg[24]+0.2165063509461096*favg[9]+0.125*favg[2])+0.125*(alpha[19]*favg[21]+favg[19]*alpha[21])-0.8660254037844386*fjump[18]+alpha[0]*(0.2165063509461096*favg[18]+0.125*favg[7])+alpha[5]*(0.2165063509461096*favg[17]+0.125*favg[6])+alpha[6]*(0.2165063509461096*favg[16]+0.125*favg[5])+0.125*alpha[1]*favg[15]-0.5*fjump[7]; 
  Ghat[11] = alpha[11]*(0.3307189138830738*favg[34]+0.138320833793122*favg[25]+0.2795084971874737*favg[14]+0.07985957062499249*favg[11]+0.2165063509461096*favg[4]+0.125*favg[0])+alpha[1]*(0.10978875820671*favg[31]+0.25*favg[28]+0.1936491673103708*favg[8]+0.1118033988749895*favg[1])+alpha[31]*(0.07453559924999298*favg[31]+0.2454951265154914*favg[28]+0.1901597073139162*favg[8]+0.10978875820671*favg[1])+alpha[21]*(0.2795084971874737*favg[30]+0.07985957062499249*favg[21]+0.2165063509461096*favg[10]+0.125*favg[3])+alpha[19]*(0.2795084971874737*favg[29]+0.07985957062499249*favg[19]+0.2165063509461096*favg[9]+0.125*favg[2])-0.8660254037844386*fjump[25]+alpha[0]*(0.2165063509461096*favg[25]+0.125*favg[11])+0.125*(alpha[3]*favg[21]+alpha[2]*favg[19])+alpha[6]*(0.1936491673103708*favg[17]+0.1118033988749895*favg[6])+alpha[5]*(0.1936491673103708*favg[16]+0.1118033988749895*favg[5])-0.5*fjump[11]; 
  Ghat[12] = alpha[2]*(0.10978875820671*favg[32]+0.25*favg[29]+0.1936491673103708*favg[9]+0.1118033988749895*favg[2])-0.8660254037844386*fjump[26]+alpha[0]*(0.2165063509461096*favg[26]+0.125*favg[12])+0.125*(alpha[3]*favg[22]+alpha[1]*favg[20])+0.1118033988749895*alpha[19]*favg[19]+alpha[5]*(0.1936491673103708*favg[16]+0.1118033988749895*favg[5])-0.5*fjump[12]; 
  Ghat[13] = alpha[3]*(0.10978875820671*favg[33]+0.25*favg[30]+0.1936491673103708*favg[10]+0.1118033988749895*favg[3])-0.8660254037844386*fjump[27]+alpha[0]*(0.2165063509461096*favg[27]+0.125*favg[13])+0.125*(alpha[2]*favg[24]+alpha[1]*favg[23])+0.1118033988749895*alpha[21]*favg[21]+alpha[6]*(0.1936491673103708*favg[17]+0.1118033988749895*favg[6])-0.5*fjump[13]; 
  Ghat[15] = alpha[5]*(0.2795084971874737*favg[30]+0.1118033988749895*(favg[22]+favg[21])+0.2165063509461096*favg[10]+0.125*favg[3])+alpha[6]*(0.2795084971874737*favg[29]+0.1118033988749895*(favg[24]+favg[19])+0.2165063509461096*favg[9]+0.125*favg[2])+(0.1936491673103708*favg[16]+0.1118033988749895*favg[5])*alpha[21]+(0.1936491673103708*favg[17]+0.1118033988749895*favg[6])*alpha[19]+alpha[1]*(0.2165063509461096*favg[18]+0.125*favg[7])+alpha[2]*(0.2165063509461096*favg[17]+0.125*favg[6])+alpha[3]*(0.2165063509461096*favg[16]+0.125*favg[5])-0.5*fjump[15]+(0.1118033988749895*alpha[11]+0.125*alpha[0])*favg[15]; 
  Ghat[19] = alpha[19]*(0.3307189138830738*favg[34]+0.1936491673103708*favg[26]+0.138320833793122*favg[25]+0.2795084971874737*favg[14]+0.1118033988749895*favg[12]+0.07985957062499249*favg[11]+0.2165063509461096*favg[4]+0.125*favg[0])+alpha[5]*(0.10978875820671*favg[31]+0.25*favg[28]+0.1*favg[20]+0.1936491673103708*favg[8]+0.1118033988749895*favg[1])+(0.1901597073139162*favg[16]+0.10978875820671*favg[5])*alpha[31]+alpha[11]*(0.2795084971874737*favg[29]+0.07985957062499249*favg[19]+0.2165063509461096*favg[9]+0.125*favg[2])+alpha[2]*(0.2165063509461096*favg[25]+0.125*favg[11])+(0.2165063509461096*favg[18]+0.125*favg[7])*alpha[21]-0.5*fjump[19]+0.125*alpha[0]*favg[19]+alpha[1]*(0.1936491673103708*favg[16]+0.1118033988749895*favg[5])+0.1118033988749895*alpha[6]*favg[15]; 
  Ghat[20] = alpha[5]*(0.10978875820671*favg[32]+0.25*favg[29]+0.1*favg[19]+0.1936491673103708*favg[9]+0.1118033988749895*favg[2])+alpha[1]*(0.2165063509461096*favg[26]+0.125*favg[12])+0.125*alpha[6]*favg[22]-0.5*fjump[20]+(0.1118033988749895*alpha[11]+0.125*alpha[0])*favg[20]+(0.1732050807568877*favg[16]+0.1*favg[5])*alpha[19]+alpha[2]*(0.1936491673103708*favg[16]+0.1118033988749895*favg[5]); 
  Ghat[21] = alpha[21]*(0.3307189138830738*favg[34]+0.1936491673103708*favg[27]+0.138320833793122*favg[25]+0.2795084971874737*favg[14]+0.1118033988749895*favg[13]+0.07985957062499249*favg[11]+0.2165063509461096*favg[4]+0.125*favg[0])+alpha[6]*(0.10978875820671*favg[31]+0.25*favg[28]+0.1*favg[23]+0.1936491673103708*favg[8]+0.1118033988749895*favg[1])+(0.1901597073139162*favg[17]+0.10978875820671*favg[6])*alpha[31]+alpha[11]*(0.2795084971874737*favg[30]+0.07985957062499249*favg[21]+0.2165063509461096*favg[10]+0.125*favg[3])+alpha[3]*(0.2165063509461096*favg[25]+0.125*favg[11])-0.5*fjump[21]+0.125*alpha[0]*favg[21]+(0.2165063509461096*favg[18]+0.125*favg[7])*alpha[19]+alpha[1]*(0.1936491673103708*favg[17]+0.1118033988749895*favg[6])+0.1118033988749895*alpha[5]*favg[15]; 
  Ghat[22] = alpha[3]*(0.2165063509461096*favg[26]+0.125*favg[12])-0.5*fjump[22]+0.125*(alpha[0]*favg[22]+alpha[6]*favg[20])+alpha[2]*(0.1936491673103708*favg[18]+0.1118033988749895*favg[7])+0.1118033988749895*alpha[5]*favg[15]; 
  Ghat[23] = alpha[6]*(0.10978875820671*favg[33]+0.25*favg[30]+0.1*favg[21]+0.1936491673103708*favg[10]+0.1118033988749895*favg[3])+alpha[1]*(0.2165063509461096*favg[27]+0.125*favg[13])+0.125*alpha[5]*favg[24]-0.5*fjump[23]+(0.1118033988749895*alpha[11]+0.125*alpha[0])*favg[23]+(0.1732050807568877*favg[17]+0.1*favg[6])*alpha[21]+alpha[3]*(0.1936491673103708*favg[17]+0.1118033988749895*favg[6]); 
  Ghat[24] = alpha[2]*(0.2165063509461096*favg[27]+0.125*favg[13])-0.5*fjump[24]+0.125*(alpha[0]*favg[24]+alpha[5]*favg[23])+alpha[3]*(0.1936491673103708*favg[18]+0.1118033988749895*favg[7])+0.1118033988749895*alpha[6]*favg[15]; 
  Ghat[31] = alpha[31]*(0.3307189138830738*favg[34]+0.1290994448735806*favg[25]+0.2795084971874737*favg[14]+0.07453559924999298*favg[11]+0.2165063509461096*favg[4]+0.125*favg[0])-0.5*fjump[31]+0.125*alpha[0]*favg[31]+alpha[11]*(0.07453559924999298*favg[31]+0.2454951265154914*favg[28]+0.1901597073139162*favg[8]+0.10978875820671*favg[1])+alpha[1]*(0.1901597073139162*favg[25]+0.10978875820671*favg[11])+0.10978875820671*alpha[6]*favg[21]+(0.1901597073139162*favg[17]+0.10978875820671*favg[6])*alpha[21]+0.10978875820671*alpha[5]*favg[19]+(0.1901597073139162*favg[16]+0.10978875820671*favg[5])*alpha[19]; 
  Ghat[32] = (-0.5*fjump[32])+0.125*alpha[0]*favg[32]+alpha[2]*(0.1901597073139162*favg[26]+0.10978875820671*favg[12])+0.10978875820671*alpha[5]*favg[20]; 
  Ghat[33] = (-0.5*fjump[33])+0.125*alpha[0]*favg[33]+alpha[3]*(0.1901597073139162*favg[27]+0.10978875820671*favg[13])+0.10978875820671*alpha[6]*favg[23]; 

  outr[0] += 0.5*Ghat[0]*dv12r; 
  outr[1] += 0.5*Ghat[1]*dv12r; 
  outr[2] += 0.5*Ghat[2]*dv12r; 
  outr[3] += 0.5*Ghat[3]*dv12r; 
  outr[4] += -0.8660254037844386*Ghat[0]*dv12r; 
  outr[5] += 0.5*Ghat[5]*dv12r; 
  outr[6] += 0.5*Ghat[6]*dv12r; 
  outr[7] += 0.5*Ghat[7]*dv12r; 
  outr[8] += -0.8660254037844386*Ghat[1]*dv12r; 
  outr[9] += -0.8660254037844386*Ghat[2]*dv12r; 
  outr[10] += -0.8660254037844386*Ghat[3]*dv12r; 
  outr[11] += 0.5*Ghat[11]*dv12r; 
  outr[12] += 0.5*Ghat[12]*dv12r; 
  outr[13] += 0.5*Ghat[13]*dv12r; 
  outr[14] += 1.118033988749895*Ghat[0]*dv12r; 
  outr[15] += 0.5*Ghat[15]*dv12r; 
  outr[16] += -0.8660254037844386*Ghat[5]*dv12r; 
  outr[17] += -0.8660254037844386*Ghat[6]*dv12r; 
  outr[18] += -0.8660254037844386*Ghat[7]*dv12r; 
  outr[19] += 0.5*Ghat[19]*dv12r; 
  outr[20] += 0.5*Ghat[20]*dv12r; 
  outr[21] += 0.5*Ghat[21]*dv12r; 
  outr[22] += 0.5*Ghat[22]*dv12r; 
  outr[23] += 0.5*Ghat[23]*dv12r; 
  outr[24] += 0.5*Ghat[24]*dv12r; 
  outr[25] += -0.8660254037844387*Ghat[11]*dv12r; 
  outr[26] += -0.8660254037844387*Ghat[12]*dv12r; 
  outr[27] += -0.8660254037844387*Ghat[13]*dv12r; 
  outr[28] += 1.118033988749895*Ghat[1]*dv12r; 
  outr[29] += 1.118033988749895*Ghat[2]*dv12r; 
  outr[30] += 1.118033988749895*Ghat[3]*dv12r; 
  outr[31] += 0.5*Ghat[31]*dv12r; 
  outr[32] += 0.5*Ghat[32]*dv12r; 
  outr[33] += 0.5*Ghat[33]*dv12r; 
  outr[34] += -1.322875655532295*Ghat[0]*dv12r; 

  outl[0] += -0.5*Ghat[0]*dv12l; 
  outl[1] += -0.5*Ghat[1]*dv12l; 
  outl[2] += -0.5*Ghat[2]*dv12l; 
  outl[3] += -0.5*Ghat[3]*dv12l; 
  outl[4] += -0.8660254037844386*Ghat[0]*dv12l; 
  outl[5] += -0.5*Ghat[5]*dv12l; 
  outl[6] += -0.5*Ghat[6]*dv12l; 
  outl[7] += -0.5*Ghat[7]*dv12l; 
  outl[8] += -0.8660254037844386*Ghat[1]*dv12l; 
  outl[9] += -0.8660254037844386*Ghat[2]*dv12l; 
  outl[10] += -0.8660254037844386*Ghat[3]*dv12l; 
  outl[11] += -0.5*Ghat[11]*dv12l; 
  outl[12] += -0.5*Ghat[12]*dv12l; 
  outl[13] += -0.5*Ghat[13]*dv12l; 
  outl[14] += -1.118033988749895*Ghat[0]*dv12l; 
  outl[15] += -0.5*Ghat[15]*dv12l; 
  outl[16] += -0.8660254037844386*Ghat[5]*dv12l; 
  outl[17] += -0.8660254037844386*Ghat[6]*dv12l; 
  outl[18] += -0.8660254037844386*Ghat[7]*dv12l; 
  outl[19] += -0.5*Ghat[19]*dv12l; 
  outl[20] += -0.5*Ghat[20]*dv12l; 
  outl[21] += -0.5*Ghat[21]*dv12l; 
  outl[22] += -0.5*Ghat[22]*dv12l; 
  outl[23] += -0.5*Ghat[23]*dv12l; 
  outl[24] += -0.5*Ghat[24]*dv12l; 
  outl[25] += -0.8660254037844387*Ghat[11]*dv12l; 
  outl[26] += -0.8660254037844387*Ghat[12]*dv12l; 
  outl[27] += -0.8660254037844387*Ghat[13]*dv12l; 
  outl[28] += -1.118033988749895*Ghat[1]*dv12l; 
  outl[29] += -1.118033988749895*Ghat[2]*dv12l; 
  outl[30] += -1.118033988749895*Ghat[3]*dv12l; 
  outl[31] += -0.5*Ghat[31]*dv12l; 
  outl[32] += -0.5*Ghat[32]*dv12l; 
  outl[33] += -0.5*Ghat[33]*dv12l; 
  outl[34] += -1.322875655532295*Ghat[0]*dv12l; 
return std::abs(amid); 
} 
