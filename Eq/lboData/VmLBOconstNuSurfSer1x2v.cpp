#include <VmLBOModDecl.h> 
double VmLBOconstNuSurf1x2vSer_VX_P1(const double *wl, const double *wr, const double *dxvl, const double *dxvr, const double nuSum, const double vMuMidMax, const double *nuUSum, const double *nuVtSqSum, const double *fl, const double *fr, double *outl, double *outr) 
{ 
  // w[3]:          Cell-center coordinates. 
  // dxv[3]:        Cell spacing. 
  // nuSum:         collisionalities added (self and cross species collisionalities). 
  // vMuMidMax:     maximum midpoint value of v-u. 
  // nuUSum[4]:     sum of bulk velocities times their respective collisionalities. 
  // nuVtSqSum[2]:  sum of thermal speeds squared time their respective collisionalities. 
  // fl/fr:         Distribution function in left/right cells 
  // outl/outr:     Incremented distribution function in left/right cells 
  double rdv = 1.0/dxvl[1]; 
  double rdv2L = 2.0/dxvl[1]; 
  double rdv2R = 2.0/dxvr[1]; 
  double rdvSq4L = 4.0/(dxvl[1]*dxvl[1]); 
  double rdvSq4R = 4.0/(dxvr[1]*dxvr[1]); 

  const double *sumNuUx = &nuUSum[0]; 

  double favg[8]; 
  favg[0] = 1*fr[0]+fl[0]; 
  favg[1] = 1*fr[1]+fl[1]; 
  favg[2] = -1*fr[2]+fl[2]; 
  favg[3] = 1*fr[3]+fl[3]; 
  favg[4] = -1*fr[4]+fl[4]; 
  favg[5] = 1*fr[5]+fl[5]; 
  favg[6] = -1*fr[6]+fl[6]; 
  favg[7] = -1*fr[7]+fl[7]; 

  double fjump[8]; 
  fjump[0] = nuSum*vMuMidMax*(fl[0]-(1*fr[0])); 
  fjump[1] = nuSum*vMuMidMax*(fl[1]-(1*fr[1])); 
  fjump[2] = nuSum*vMuMidMax*(fl[2]-(-1*fr[2])); 
  fjump[3] = nuSum*vMuMidMax*(fl[3]-(1*fr[3])); 
  fjump[4] = nuSum*vMuMidMax*(fl[4]-(-1*fr[4])); 
  fjump[5] = nuSum*vMuMidMax*(fl[5]-(1*fr[5])); 
  fjump[6] = nuSum*vMuMidMax*(fl[6]-(-1*fr[6])); 
  fjump[7] = nuSum*vMuMidMax*(fl[7]-(-1*fr[7])); 

  double alphaDrag[2]; 
  alphaDrag[0] = 1.414213562373095*wl[1]*nuSum+0.7071067811865475*dxvl[1]*nuSum-1.0*sumNuUx[0]; 
  alphaDrag[1] = -1.0*sumNuUx[1]; 

  double Ghat[8]; 
  for(unsigned short int i=0; i<8; ++i){ 
    Ghat[i]=0.0; 
  }; 

  Ghat[0] = ((-1.530931089239486*nuVtSqSum[1]*fr[4])-1.530931089239486*nuVtSqSum[1]*fl[4]-1.530931089239486*nuVtSqSum[0]*fr[2]-1.530931089239486*nuVtSqSum[0]*fl[2]+1.590990257669731*fr[1]*nuVtSqSum[1]-1.590990257669731*fl[1]*nuVtSqSum[1]+1.590990257669731*fr[0]*nuVtSqSum[0]-1.590990257669731*fl[0]*nuVtSqSum[0])*rdv+alphaDrag[1]*(0.6123724356957944*favg[4]+0.3535533905932737*favg[1])-0.8660254037844386*fjump[2]+alphaDrag[0]*(0.6123724356957944*favg[2]+0.3535533905932737*favg[0])-0.5*fjump[0]; 
  Ghat[1] = ((-1.530931089239486*nuVtSqSum[0]*fr[4])-1.530931089239486*nuVtSqSum[0]*fl[4]-1.530931089239486*nuVtSqSum[1]*fr[2]-1.530931089239486*nuVtSqSum[1]*fl[2]+1.590990257669731*fr[0]*nuVtSqSum[1]-1.590990257669731*fl[0]*nuVtSqSum[1]+1.590990257669731*nuVtSqSum[0]*fr[1]-1.590990257669731*nuVtSqSum[0]*fl[1])*rdv-0.8660254037844386*fjump[4]+alphaDrag[0]*(0.6123724356957944*favg[4]+0.3535533905932737*favg[1])+alphaDrag[1]*(0.6123724356957944*favg[2]+0.3535533905932737*favg[0])-0.5*fjump[1]; 
  Ghat[3] = ((-1.530931089239486*nuVtSqSum[1]*fr[7])-1.530931089239486*nuVtSqSum[1]*fl[7]-1.530931089239486*nuVtSqSum[0]*fr[6]-1.530931089239486*nuVtSqSum[0]*fl[6]+1.590990257669731*nuVtSqSum[1]*fr[5]-1.590990257669731*nuVtSqSum[1]*fl[5]+1.590990257669731*nuVtSqSum[0]*fr[3]-1.590990257669731*nuVtSqSum[0]*fl[3])*rdv+alphaDrag[1]*(0.6123724356957944*favg[7]+0.3535533905932737*favg[5])-0.8660254037844386*fjump[6]+alphaDrag[0]*(0.6123724356957944*favg[6]+0.3535533905932737*favg[3])-0.5*fjump[3]; 
  Ghat[5] = ((-1.530931089239486*nuVtSqSum[0]*fr[7])-1.530931089239486*nuVtSqSum[0]*fl[7]-1.530931089239486*nuVtSqSum[1]*fr[6]-1.530931089239486*nuVtSqSum[1]*fl[6]+1.590990257669731*nuVtSqSum[0]*fr[5]-1.590990257669731*nuVtSqSum[0]*fl[5]+1.590990257669731*nuVtSqSum[1]*fr[3]-1.590990257669731*nuVtSqSum[1]*fl[3])*rdv-0.8660254037844386*fjump[7]+alphaDrag[0]*(0.6123724356957944*favg[7]+0.3535533905932737*favg[5])+alphaDrag[1]*(0.6123724356957944*favg[6]+0.3535533905932737*favg[3])-0.5*fjump[5]; 

  double incr1[8]; 
  incr1[0] = -0.5*Ghat[0]; 
  incr1[1] = -0.5*Ghat[1]; 
  incr1[2] = 0.8660254037844386*Ghat[0]; 
  incr1[3] = -0.5*Ghat[3]; 
  incr1[4] = 0.8660254037844386*Ghat[1]; 
  incr1[5] = -0.5*Ghat[5]; 
  incr1[6] = 0.8660254037844386*Ghat[3]; 
  incr1[7] = 0.8660254037844386*Ghat[5]; 

  double incr2[8]; 
  incr2[2] = nuVtSqSum[1]*((-0.3535533905932737*fr[4])+0.3535533905932737*fl[4]+0.3061862178478971*(fr[1]+fl[1]))+nuVtSqSum[0]*((-0.3535533905932737*fr[2])+0.3535533905932737*fl[2]+0.3061862178478971*(fr[0]+fl[0])); 
  incr2[4] = nuVtSqSum[0]*((-0.3535533905932737*fr[4])+0.3535533905932737*fl[4]+0.3061862178478971*(fr[1]+fl[1]))+nuVtSqSum[1]*((-0.3535533905932737*fr[2])+0.3535533905932737*fl[2]+0.3061862178478971*(fr[0]+fl[0])); 
  incr2[6] = nuVtSqSum[1]*((-0.3535533905932737*fr[7])+0.3535533905932737*fl[7]+0.3061862178478971*(fr[5]+fl[5]))+nuVtSqSum[0]*((-0.3535533905932737*fr[6])+0.3535533905932737*fl[6]+0.3061862178478971*(fr[3]+fl[3])); 
  incr2[7] = nuVtSqSum[0]*((-0.3535533905932737*fr[7])+0.3535533905932737*fl[7]+0.3061862178478971*(fr[5]+fl[5]))+nuVtSqSum[1]*((-0.3535533905932737*fr[6])+0.3535533905932737*fl[6]+0.3061862178478971*(fr[3]+fl[3])); 

  outr[0] += incr1[0]*rdv2R; 
  outr[1] += incr1[1]*rdv2R; 
  outr[2] += incr2[2]*rdvSq4R+incr1[2]*rdv2R; 
  outr[3] += incr1[3]*rdv2R; 
  outr[4] += incr2[4]*rdvSq4R+incr1[4]*rdv2R; 
  outr[5] += incr1[5]*rdv2R; 
  outr[6] += incr2[6]*rdvSq4R+incr1[6]*rdv2R; 
  outr[7] += incr2[7]*rdvSq4R+incr1[7]*rdv2R; 

  outl[0] += -1.0*incr1[0]*rdv2L; 
  outl[1] += -1.0*incr1[1]*rdv2L; 
  outl[2] += incr1[2]*rdv2L-1.0*incr2[2]*rdvSq4L; 
  outl[3] += -1.0*incr1[3]*rdv2L; 
  outl[4] += incr1[4]*rdv2L-1.0*incr2[4]*rdvSq4L; 
  outl[5] += -1.0*incr1[5]*rdv2L; 
  outl[6] += incr1[6]*rdv2L-1.0*incr2[6]*rdvSq4L; 
  outl[7] += incr1[7]*rdv2L-1.0*incr2[7]*rdvSq4L; 

  return std::abs(wl[1]-(0.7071067811865475*sumNuUx[0])/nuSum); 
} 
double VmLBOconstNuSurf1x2vSer_VX_P2(const double *wl, const double *wr, const double *dxvl, const double *dxvr, const double nuSum, const double vMuMidMax, const double *nuUSum, const double *nuVtSqSum, const double *fl, const double *fr, double *outl, double *outr) 
{ 
  // w[3]:          Cell-center coordinates. 
  // dxv[3]:        Cell spacing. 
  // nuSum:         collisionalities added (self and cross species collisionalities). 
  // vMuMidMax:     maximum midpoint value of v-u. 
  // nuUSum[6]:     sum of bulk velocities times their respective collisionalities. 
  // nuVtSqSum[3]:  sum of thermal speeds squared time their respective collisionalities. 
  // fl/fr:         Distribution function in left/right cells 
  // outl/outr:     Incremented distribution function in left/right cells 
  double rdv = 1.0/dxvl[1]; 
  double rdv2L = 2.0/dxvl[1]; 
  double rdv2R = 2.0/dxvr[1]; 
  double rdvSq4L = 4.0/(dxvl[1]*dxvl[1]); 
  double rdvSq4R = 4.0/(dxvr[1]*dxvr[1]); 

  const double *sumNuUx = &nuUSum[0]; 

  double favg[20]; 
  favg[0] = 1*fr[0]+fl[0]; 
  favg[1] = 1*fr[1]+fl[1]; 
  favg[2] = -1*fr[2]+fl[2]; 
  favg[3] = 1*fr[3]+fl[3]; 
  favg[4] = -1*fr[4]+fl[4]; 
  favg[5] = 1*fr[5]+fl[5]; 
  favg[6] = -1*fr[6]+fl[6]; 
  favg[7] = 1*fr[7]+fl[7]; 
  favg[8] = 1*fr[8]+fl[8]; 
  favg[9] = 1*fr[9]+fl[9]; 
  favg[10] = -1*fr[10]+fl[10]; 
  favg[11] = -1*fr[11]+fl[11]; 
  favg[12] = 1*fr[12]+fl[12]; 
  favg[13] = 1*fr[13]+fl[13]; 
  favg[14] = 1*fr[14]+fl[14]; 
  favg[15] = 1*fr[15]+fl[15]; 
  favg[16] = -1*fr[16]+fl[16]; 
  favg[17] = -1*fr[17]+fl[17]; 
  favg[18] = 1*fr[18]+fl[18]; 
  favg[19] = -1*fr[19]+fl[19]; 

  double fjump[20]; 
  fjump[0] = nuSum*vMuMidMax*(fl[0]-(1*fr[0])); 
  fjump[1] = nuSum*vMuMidMax*(fl[1]-(1*fr[1])); 
  fjump[2] = nuSum*vMuMidMax*(fl[2]-(-1*fr[2])); 
  fjump[3] = nuSum*vMuMidMax*(fl[3]-(1*fr[3])); 
  fjump[4] = nuSum*vMuMidMax*(fl[4]-(-1*fr[4])); 
  fjump[5] = nuSum*vMuMidMax*(fl[5]-(1*fr[5])); 
  fjump[6] = nuSum*vMuMidMax*(fl[6]-(-1*fr[6])); 
  fjump[7] = nuSum*vMuMidMax*(fl[7]-(1*fr[7])); 
  fjump[8] = nuSum*vMuMidMax*(fl[8]-(1*fr[8])); 
  fjump[9] = nuSum*vMuMidMax*(fl[9]-(1*fr[9])); 
  fjump[10] = nuSum*vMuMidMax*(fl[10]-(-1*fr[10])); 
  fjump[11] = nuSum*vMuMidMax*(fl[11]-(-1*fr[11])); 
  fjump[12] = nuSum*vMuMidMax*(fl[12]-(1*fr[12])); 
  fjump[13] = nuSum*vMuMidMax*(fl[13]-(1*fr[13])); 
  fjump[14] = nuSum*vMuMidMax*(fl[14]-(1*fr[14])); 
  fjump[15] = nuSum*vMuMidMax*(fl[15]-(1*fr[15])); 
  fjump[16] = nuSum*vMuMidMax*(fl[16]-(-1*fr[16])); 
  fjump[17] = nuSum*vMuMidMax*(fl[17]-(-1*fr[17])); 
  fjump[18] = nuSum*vMuMidMax*(fl[18]-(1*fr[18])); 
  fjump[19] = nuSum*vMuMidMax*(fl[19]-(-1*fr[19])); 

  double alphaDrag[3]; 
  alphaDrag[0] = 1.414213562373095*wl[1]*nuSum+0.7071067811865475*dxvl[1]*nuSum-1.0*sumNuUx[0]; 
  alphaDrag[1] = -1.0*sumNuUx[1]; 
  alphaDrag[2] = -1.0*sumNuUx[2]; 

  double Ghat[20]; 
  for(unsigned short int i=0; i<20; ++i){ 
    Ghat[i]=0.0; 
  }; 

  Ghat[0] = (1.897366596101028*nuVtSqSum[1]*fr[12]-1.897366596101028*nuVtSqSum[1]*fl[12]-3.368048396326869*nuVtSqSum[2]*fr[11]-3.368048396326869*nuVtSqSum[2]*fl[11]+1.897366596101028*nuVtSqSum[0]*fr[8]-1.897366596101028*nuVtSqSum[0]*fl[8]+2.651650429449552*nuVtSqSum[2]*fr[7]-2.651650429449552*nuVtSqSum[2]*fl[7]-3.368048396326869*nuVtSqSum[1]*fr[4]-3.368048396326869*nuVtSqSum[1]*fl[4]-3.368048396326869*nuVtSqSum[0]*fr[2]-3.368048396326869*nuVtSqSum[0]*fl[2]+2.651650429449552*fr[1]*nuVtSqSum[1]-2.651650429449552*fl[1]*nuVtSqSum[1]+2.651650429449552*fr[0]*nuVtSqSum[0]-2.651650429449552*fl[0]*nuVtSqSum[0])*rdv+alphaDrag[1]*(0.7905694150420948*favg[12]+0.6123724356957944*favg[4]+0.3535533905932737*favg[1])+alphaDrag[2]*(0.6123724356957944*favg[11]+0.3535533905932737*favg[7])-1.118033988749895*fjump[8]+alphaDrag[0]*(0.7905694150420947*favg[8]+0.6123724356957944*favg[2]+0.3535533905932737*favg[0])-0.8660254037844386*fjump[2]-0.5*fjump[0]; 
  Ghat[1] = (1.697056274847714*nuVtSqSum[2]*fr[12]+1.897366596101028*nuVtSqSum[0]*fr[12]-1.697056274847714*nuVtSqSum[2]*fl[12]-1.897366596101028*nuVtSqSum[0]*fl[12]-3.012474066278414*nuVtSqSum[1]*fr[11]-3.012474066278414*nuVtSqSum[1]*fl[11]+1.897366596101028*nuVtSqSum[1]*fr[8]-1.897366596101028*nuVtSqSum[1]*fl[8]+2.371708245126284*nuVtSqSum[1]*fr[7]-2.371708245126284*nuVtSqSum[1]*fl[7]-3.012474066278413*nuVtSqSum[2]*fr[4]-3.368048396326869*nuVtSqSum[0]*fr[4]-3.012474066278413*nuVtSqSum[2]*fl[4]-3.368048396326869*nuVtSqSum[0]*fl[4]+2.371708245126284*fr[1]*nuVtSqSum[2]-2.371708245126284*fl[1]*nuVtSqSum[2]-3.368048396326869*nuVtSqSum[1]*fr[2]-3.368048396326869*nuVtSqSum[1]*fl[2]+2.651650429449552*fr[0]*nuVtSqSum[1]-2.651650429449552*fl[0]*nuVtSqSum[1]+2.651650429449552*nuVtSqSum[0]*fr[1]-2.651650429449552*nuVtSqSum[0]*fl[1])*rdv-1.118033988749895*fjump[12]+alphaDrag[0]*(0.7905694150420948*favg[12]+0.6123724356957944*favg[4]+0.3535533905932737*favg[1])+alphaDrag[2]*(0.7071067811865475*favg[12]+0.5477225575051661*favg[4]+0.3162277660168379*favg[1])+alphaDrag[1]*(0.5477225575051661*favg[11]+0.7905694150420947*favg[8]+0.3162277660168379*favg[7]+0.6123724356957944*favg[2]+0.3535533905932737*favg[0])-0.8660254037844386*fjump[4]-0.5*fjump[1]; 
  Ghat[3] = (1.897366596101028*nuVtSqSum[1]*fr[18]-1.897366596101028*nuVtSqSum[1]*fl[18]-3.368048396326869*nuVtSqSum[2]*fr[17]-3.368048396326869*nuVtSqSum[2]*fl[17]+1.897366596101028*nuVtSqSum[0]*fr[14]-1.897366596101028*nuVtSqSum[0]*fl[14]+2.651650429449552*nuVtSqSum[2]*fr[13]-2.651650429449552*nuVtSqSum[2]*fl[13]-3.368048396326869*nuVtSqSum[1]*fr[10]-3.368048396326869*nuVtSqSum[1]*fl[10]-3.368048396326869*nuVtSqSum[0]*fr[6]-3.368048396326869*nuVtSqSum[0]*fl[6]+2.651650429449552*nuVtSqSum[1]*fr[5]-2.651650429449552*nuVtSqSum[1]*fl[5]+2.651650429449552*nuVtSqSum[0]*fr[3]-2.651650429449552*nuVtSqSum[0]*fl[3])*rdv+alphaDrag[1]*(0.7905694150420947*favg[18]+0.6123724356957944*favg[10]+0.3535533905932737*favg[5])+alphaDrag[2]*(0.6123724356957944*favg[17]+0.3535533905932737*favg[13])-1.118033988749895*fjump[14]+alphaDrag[0]*(0.7905694150420948*favg[14]+0.6123724356957944*favg[6]+0.3535533905932737*favg[3])-0.8660254037844386*fjump[6]-0.5*fjump[3]; 
  Ghat[5] = (1.697056274847714*nuVtSqSum[2]*fr[18]+1.897366596101028*nuVtSqSum[0]*fr[18]-1.697056274847714*nuVtSqSum[2]*fl[18]-1.897366596101028*nuVtSqSum[0]*fl[18]-3.012474066278413*nuVtSqSum[1]*fr[17]-3.012474066278413*nuVtSqSum[1]*fl[17]+1.897366596101028*nuVtSqSum[1]*fr[14]-1.897366596101028*nuVtSqSum[1]*fl[14]+2.371708245126284*nuVtSqSum[1]*fr[13]-2.371708245126284*nuVtSqSum[1]*fl[13]-3.012474066278413*nuVtSqSum[2]*fr[10]-3.368048396326869*nuVtSqSum[0]*fr[10]-3.012474066278413*nuVtSqSum[2]*fl[10]-3.368048396326869*nuVtSqSum[0]*fl[10]-3.368048396326869*nuVtSqSum[1]*fr[6]-3.368048396326869*nuVtSqSum[1]*fl[6]+2.371708245126284*nuVtSqSum[2]*fr[5]+2.651650429449552*nuVtSqSum[0]*fr[5]-2.371708245126284*nuVtSqSum[2]*fl[5]-2.651650429449552*nuVtSqSum[0]*fl[5]+2.651650429449552*nuVtSqSum[1]*fr[3]-2.651650429449552*nuVtSqSum[1]*fl[3])*rdv-1.118033988749895*fjump[18]+alphaDrag[0]*(0.7905694150420947*favg[18]+0.6123724356957944*favg[10]+0.3535533905932737*favg[5])+alphaDrag[2]*(0.7071067811865475*favg[18]+0.5477225575051661*favg[10]+0.3162277660168379*favg[5])+alphaDrag[1]*(0.5477225575051661*favg[17]+0.7905694150420948*favg[14]+0.3162277660168379*favg[13]+0.6123724356957944*favg[6]+0.3535533905932737*favg[3])-0.8660254037844386*fjump[10]-0.5*fjump[5]; 
  Ghat[7] = (1.697056274847714*nuVtSqSum[1]*fr[12]-1.697056274847714*nuVtSqSum[1]*fl[12]-2.151767190198866*nuVtSqSum[2]*fr[11]-3.368048396326869*nuVtSqSum[0]*fr[11]-2.151767190198866*nuVtSqSum[2]*fl[11]-3.368048396326869*nuVtSqSum[0]*fl[11]+1.897366596101028*nuVtSqSum[2]*fr[8]-1.897366596101028*nuVtSqSum[2]*fl[8]+1.694077317947346*nuVtSqSum[2]*fr[7]+2.651650429449552*nuVtSqSum[0]*fr[7]-1.694077317947346*nuVtSqSum[2]*fl[7]-2.651650429449552*nuVtSqSum[0]*fl[7]-3.012474066278413*nuVtSqSum[1]*fr[4]-3.012474066278413*nuVtSqSum[1]*fl[4]-3.368048396326869*fr[2]*nuVtSqSum[2]-3.368048396326869*fl[2]*nuVtSqSum[2]+2.651650429449552*fr[0]*nuVtSqSum[2]-2.651650429449552*fl[0]*nuVtSqSum[2]+2.371708245126284*fr[1]*nuVtSqSum[1]-2.371708245126284*fl[1]*nuVtSqSum[1])*rdv+alphaDrag[1]*(0.7071067811865475*favg[12]+0.5477225575051661*favg[4]+0.3162277660168379*favg[1])-0.8660254037844387*fjump[11]+alphaDrag[0]*(0.6123724356957944*favg[11]+0.3535533905932737*favg[7])+alphaDrag[2]*(0.3912303982179757*favg[11]+0.7905694150420947*favg[8]+0.2258769757263128*favg[7]+0.6123724356957944*favg[2]+0.3535533905932737*favg[0])-0.5*fjump[7]; 
  Ghat[9] = ((-3.368048396326869*nuVtSqSum[1]*fr[19])-3.368048396326869*nuVtSqSum[1]*fl[19]-3.368048396326869*nuVtSqSum[0]*fr[16]-3.368048396326869*nuVtSqSum[0]*fl[16]+2.651650429449552*nuVtSqSum[1]*fr[15]-2.651650429449552*nuVtSqSum[1]*fl[15]+2.651650429449552*nuVtSqSum[0]*fr[9]-2.651650429449552*nuVtSqSum[0]*fl[9])*rdv+alphaDrag[1]*(0.6123724356957944*favg[19]+0.3535533905932737*favg[15])-0.8660254037844387*fjump[16]+alphaDrag[0]*(0.6123724356957944*favg[16]+0.3535533905932737*favg[9])-0.5*fjump[9]; 
  Ghat[13] = (1.697056274847714*nuVtSqSum[1]*fr[18]-1.697056274847714*nuVtSqSum[1]*fl[18]-2.151767190198866*nuVtSqSum[2]*fr[17]-3.368048396326869*nuVtSqSum[0]*fr[17]-2.151767190198866*nuVtSqSum[2]*fl[17]-3.368048396326869*nuVtSqSum[0]*fl[17]+1.897366596101028*nuVtSqSum[2]*fr[14]-1.897366596101028*nuVtSqSum[2]*fl[14]+1.694077317947346*nuVtSqSum[2]*fr[13]+2.651650429449552*nuVtSqSum[0]*fr[13]-1.694077317947346*nuVtSqSum[2]*fl[13]-2.651650429449552*nuVtSqSum[0]*fl[13]-3.012474066278414*nuVtSqSum[1]*fr[10]-3.012474066278414*nuVtSqSum[1]*fl[10]-3.368048396326869*nuVtSqSum[2]*fr[6]-3.368048396326869*nuVtSqSum[2]*fl[6]+2.371708245126284*nuVtSqSum[1]*fr[5]-2.371708245126284*nuVtSqSum[1]*fl[5]+2.651650429449552*nuVtSqSum[2]*fr[3]-2.651650429449552*nuVtSqSum[2]*fl[3])*rdv+alphaDrag[1]*(0.7071067811865475*favg[18]+0.5477225575051661*favg[10]+0.3162277660168379*favg[5])-0.8660254037844387*fjump[17]+alphaDrag[0]*(0.6123724356957944*favg[17]+0.3535533905932737*favg[13])+alphaDrag[2]*(0.3912303982179757*favg[17]+0.7905694150420947*favg[14]+0.2258769757263128*favg[13]+0.6123724356957944*favg[6]+0.3535533905932737*favg[3])-0.5*fjump[13]; 
  Ghat[15] = ((-3.012474066278414*nuVtSqSum[2]*fr[19])-3.368048396326869*nuVtSqSum[0]*fr[19]-3.012474066278414*nuVtSqSum[2]*fl[19]-3.368048396326869*nuVtSqSum[0]*fl[19]-3.368048396326869*nuVtSqSum[1]*fr[16]-3.368048396326869*nuVtSqSum[1]*fl[16]+2.371708245126284*nuVtSqSum[2]*fr[15]+2.651650429449552*nuVtSqSum[0]*fr[15]-2.371708245126284*nuVtSqSum[2]*fl[15]-2.651650429449552*nuVtSqSum[0]*fl[15]+2.651650429449552*nuVtSqSum[1]*fr[9]-2.651650429449552*nuVtSqSum[1]*fl[9])*rdv-0.8660254037844387*fjump[19]+alphaDrag[0]*(0.6123724356957944*favg[19]+0.3535533905932737*favg[15])+alphaDrag[2]*(0.5477225575051661*favg[19]+0.3162277660168379*favg[15])+alphaDrag[1]*(0.6123724356957944*favg[16]+0.3535533905932737*favg[9])-0.5*fjump[15]; 

  double incr1[20]; 
  incr1[0] = -0.5*Ghat[0]; 
  incr1[1] = -0.5*Ghat[1]; 
  incr1[2] = 0.8660254037844386*Ghat[0]; 
  incr1[3] = -0.5*Ghat[3]; 
  incr1[4] = 0.8660254037844386*Ghat[1]; 
  incr1[5] = -0.5*Ghat[5]; 
  incr1[6] = 0.8660254037844386*Ghat[3]; 
  incr1[7] = -0.5*Ghat[7]; 
  incr1[8] = -1.118033988749895*Ghat[0]; 
  incr1[9] = -0.5*Ghat[9]; 
  incr1[10] = 0.8660254037844386*Ghat[5]; 
  incr1[11] = 0.8660254037844387*Ghat[7]; 
  incr1[12] = -1.118033988749895*Ghat[1]; 
  incr1[13] = -0.5*Ghat[13]; 
  incr1[14] = -1.118033988749895*Ghat[3]; 
  incr1[15] = -0.5*Ghat[15]; 
  incr1[16] = 0.8660254037844387*Ghat[9]; 
  incr1[17] = 0.8660254037844387*Ghat[13]; 
  incr1[18] = -1.118033988749895*Ghat[5]; 
  incr1[19] = 0.8660254037844387*Ghat[15]; 

  double incr2[20]; 
  incr2[2] = nuVtSqSum[1]*(0.2995357736356374*(fr[12]+fl[12])-0.430893194785552*fr[4]+0.430893194785552*fl[4]+0.3061862178478971*(fr[1]+fl[1]))+nuVtSqSum[2]*((-0.430893194785552*fr[11])+0.430893194785552*fl[11]+0.3061862178478971*(fr[7]+fl[7]))+nuVtSqSum[0]*(0.2995357736356374*(fr[8]+fl[8])-0.430893194785552*fr[2]+0.430893194785552*fl[2]+0.3061862178478971*(fr[0]+fl[0])); 
  incr2[4] = nuVtSqSum[0]*(0.2995357736356374*(fr[12]+fl[12])-0.430893194785552*fr[4]+0.430893194785552*fl[4]+0.3061862178478971*(fr[1]+fl[1]))+nuVtSqSum[2]*(0.2679129406169099*(fr[12]+fl[12])-0.3854025898330209*fr[4]+0.3854025898330209*fl[4]+0.273861278752583*(fr[1]+fl[1]))+nuVtSqSum[1]*((-0.3854025898330209*fr[11])+0.3854025898330209*fl[11]+0.2995357736356374*(fr[8]+fl[8])+0.273861278752583*(fr[7]+fl[7])-0.430893194785552*fr[2]+0.430893194785552*fl[2]+0.3061862178478971*(fr[0]+fl[0])); 
  incr2[6] = nuVtSqSum[1]*(0.2995357736356374*(fr[18]+fl[18])-0.430893194785552*fr[10]+0.430893194785552*fl[10]+0.3061862178478971*(fr[5]+fl[5]))+nuVtSqSum[2]*((-0.430893194785552*fr[17])+0.430893194785552*fl[17]+0.3061862178478971*(fr[13]+fl[13]))+nuVtSqSum[0]*(0.2995357736356374*(fr[14]+fl[14])-0.430893194785552*fr[6]+0.430893194785552*fl[6]+0.3061862178478971*(fr[3]+fl[3])); 
  incr2[8] = nuVtSqSum[1]*((-1.160097062884178*(fr[12]+fl[12]))+1.668842167398551*fr[4]-1.668842167398551*fl[4]-1.185854122563142*(fr[1]+fl[1]))+nuVtSqSum[2]*(1.668842167398552*fr[11]-1.668842167398552*fl[11]-1.185854122563142*(fr[7]+fl[7]))+nuVtSqSum[0]*((-1.160097062884178*(fr[8]+fl[8]))+1.668842167398551*fr[2]-1.668842167398551*fl[2]-1.185854122563142*(fr[0]+fl[0])); 
  incr2[10] = nuVtSqSum[0]*(0.2995357736356374*(fr[18]+fl[18])-0.430893194785552*fr[10]+0.430893194785552*fl[10]+0.3061862178478971*(fr[5]+fl[5]))+nuVtSqSum[2]*(0.2679129406169099*(fr[18]+fl[18])-0.3854025898330209*fr[10]+0.3854025898330209*fl[10]+0.273861278752583*(fr[5]+fl[5]))+nuVtSqSum[1]*((-0.3854025898330209*fr[17])+0.3854025898330209*fl[17]+0.2995357736356374*(fr[14]+fl[14])+0.273861278752583*(fr[13]+fl[13])-0.430893194785552*fr[6]+0.430893194785552*fl[6]+0.3061862178478971*(fr[3]+fl[3])); 
  incr2[11] = nuVtSqSum[1]*(0.2679129406169099*(fr[12]+fl[12])-0.3854025898330209*fr[4]+0.3854025898330209*fl[4]+0.273861278752583*(fr[1]+fl[1]))+nuVtSqSum[2]*((-0.2752875641664436*fr[11])+0.2752875641664436*fl[11]+0.2995357736356374*(fr[8]+fl[8])+0.1956151991089878*(fr[7]+fl[7])-0.430893194785552*fr[2]+0.430893194785552*fl[2]+0.3061862178478971*(fr[0]+fl[0]))+nuVtSqSum[0]*((-0.430893194785552*fr[11])+0.430893194785552*fl[11]+0.3061862178478971*(fr[7]+fl[7])); 
  incr2[12] = nuVtSqSum[2]*((-1.037622357242749*(fr[12]+fl[12]))+1.492657812008498*fr[4]-1.492657812008498*fl[4]-1.060660171779821*(fr[1]+fl[1]))+nuVtSqSum[0]*((-1.160097062884178*(fr[12]+fl[12]))+1.668842167398552*fr[4]-1.668842167398552*fl[4]-1.185854122563142*(fr[1]+fl[1]))+nuVtSqSum[1]*(1.492657812008498*fr[11]-1.492657812008498*fl[11]-1.160097062884178*(fr[8]+fl[8])-1.060660171779821*(fr[7]+fl[7])+1.668842167398552*fr[2]-1.668842167398552*fl[2]-1.185854122563142*(fr[0]+fl[0])); 
  incr2[14] = nuVtSqSum[1]*((-1.160097062884178*(fr[18]+fl[18]))+1.668842167398552*fr[10]-1.668842167398552*fl[10]-1.185854122563142*(fr[5]+fl[5]))+nuVtSqSum[2]*(1.668842167398552*fr[17]-1.668842167398552*fl[17]-1.185854122563142*(fr[13]+fl[13]))+nuVtSqSum[0]*((-1.160097062884178*(fr[14]+fl[14]))+1.668842167398552*fr[6]-1.668842167398552*fl[6]-1.185854122563142*(fr[3]+fl[3])); 
  incr2[16] = nuVtSqSum[1]*((-0.430893194785552*fr[19])+0.430893194785552*fl[19]+0.3061862178478971*(fr[15]+fl[15]))+nuVtSqSum[0]*((-0.430893194785552*fr[16])+0.430893194785552*fl[16]+0.3061862178478971*(fr[9]+fl[9])); 
  incr2[17] = nuVtSqSum[1]*(0.2679129406169099*(fr[18]+fl[18])-0.3854025898330209*fr[10]+0.3854025898330209*fl[10]+0.273861278752583*(fr[5]+fl[5]))+nuVtSqSum[2]*((-0.2752875641664436*fr[17])+0.2752875641664436*fl[17]+0.2995357736356374*(fr[14]+fl[14])+0.1956151991089878*(fr[13]+fl[13])-0.430893194785552*fr[6]+0.430893194785552*fl[6]+0.3061862178478971*(fr[3]+fl[3]))+nuVtSqSum[0]*((-0.430893194785552*fr[17])+0.430893194785552*fl[17]+0.3061862178478971*(fr[13]+fl[13])); 
  incr2[18] = nuVtSqSum[2]*((-1.037622357242749*(fr[18]+fl[18]))+1.492657812008498*fr[10]-1.492657812008498*fl[10]-1.060660171779821*(fr[5]+fl[5]))+nuVtSqSum[0]*((-1.160097062884178*(fr[18]+fl[18]))+1.668842167398551*fr[10]-1.668842167398551*fl[10]-1.185854122563142*(fr[5]+fl[5]))+nuVtSqSum[1]*(1.492657812008498*fr[17]-1.492657812008498*fl[17]-1.160097062884178*(fr[14]+fl[14])-1.060660171779821*(fr[13]+fl[13])+1.668842167398551*fr[6]-1.668842167398551*fl[6]-1.185854122563142*(fr[3]+fl[3])); 
  incr2[19] = nuVtSqSum[2]*((-0.3854025898330209*fr[19])+0.3854025898330209*fl[19]+0.273861278752583*(fr[15]+fl[15]))+nuVtSqSum[0]*((-0.430893194785552*fr[19])+0.430893194785552*fl[19]+0.3061862178478971*(fr[15]+fl[15]))+nuVtSqSum[1]*((-0.430893194785552*fr[16])+0.430893194785552*fl[16]+0.3061862178478971*(fr[9]+fl[9])); 

  outr[0] += incr1[0]*rdv2R; 
  outr[1] += incr1[1]*rdv2R; 
  outr[2] += incr2[2]*rdvSq4R+incr1[2]*rdv2R; 
  outr[3] += incr1[3]*rdv2R; 
  outr[4] += incr2[4]*rdvSq4R+incr1[4]*rdv2R; 
  outr[5] += incr1[5]*rdv2R; 
  outr[6] += incr2[6]*rdvSq4R+incr1[6]*rdv2R; 
  outr[7] += incr1[7]*rdv2R; 
  outr[8] += incr2[8]*rdvSq4R+incr1[8]*rdv2R; 
  outr[9] += incr1[9]*rdv2R; 
  outr[10] += incr2[10]*rdvSq4R+incr1[10]*rdv2R; 
  outr[11] += incr2[11]*rdvSq4R+incr1[11]*rdv2R; 
  outr[12] += incr2[12]*rdvSq4R+incr1[12]*rdv2R; 
  outr[13] += incr1[13]*rdv2R; 
  outr[14] += incr2[14]*rdvSq4R+incr1[14]*rdv2R; 
  outr[15] += incr1[15]*rdv2R; 
  outr[16] += incr2[16]*rdvSq4R+incr1[16]*rdv2R; 
  outr[17] += incr2[17]*rdvSq4R+incr1[17]*rdv2R; 
  outr[18] += incr2[18]*rdvSq4R+incr1[18]*rdv2R; 
  outr[19] += incr2[19]*rdvSq4R+incr1[19]*rdv2R; 

  outl[0] += -1.0*incr1[0]*rdv2L; 
  outl[1] += -1.0*incr1[1]*rdv2L; 
  outl[2] += incr1[2]*rdv2L-1.0*incr2[2]*rdvSq4L; 
  outl[3] += -1.0*incr1[3]*rdv2L; 
  outl[4] += incr1[4]*rdv2L-1.0*incr2[4]*rdvSq4L; 
  outl[5] += -1.0*incr1[5]*rdv2L; 
  outl[6] += incr1[6]*rdv2L-1.0*incr2[6]*rdvSq4L; 
  outl[7] += -1.0*incr1[7]*rdv2L; 
  outl[8] += incr2[8]*rdvSq4L-1.0*incr1[8]*rdv2L; 
  outl[9] += -1.0*incr1[9]*rdv2L; 
  outl[10] += incr1[10]*rdv2L-1.0*incr2[10]*rdvSq4L; 
  outl[11] += incr1[11]*rdv2L-1.0*incr2[11]*rdvSq4L; 
  outl[12] += incr2[12]*rdvSq4L-1.0*incr1[12]*rdv2L; 
  outl[13] += -1.0*incr1[13]*rdv2L; 
  outl[14] += incr2[14]*rdvSq4L-1.0*incr1[14]*rdv2L; 
  outl[15] += -1.0*incr1[15]*rdv2L; 
  outl[16] += incr1[16]*rdv2L-1.0*incr2[16]*rdvSq4L; 
  outl[17] += incr1[17]*rdv2L-1.0*incr2[17]*rdvSq4L; 
  outl[18] += incr2[18]*rdvSq4L-1.0*incr1[18]*rdv2L; 
  outl[19] += incr1[19]*rdv2L-1.0*incr2[19]*rdvSq4L; 

  return std::abs((0.7905694150420947*sumNuUx[2])/nuSum-(0.7071067811865475*sumNuUx[0])/nuSum+wl[1]); 
} 
double VmLBOconstNuSurf1x2vSer_VX_P3(const double *wl, const double *wr, const double *dxvl, const double *dxvr, const double nuSum, const double vMuMidMax, const double *nuUSum, const double *nuVtSqSum, const double *fl, const double *fr, double *outl, double *outr) 
{ 
  // w[3]:          Cell-center coordinates. 
  // dxv[3]:        Cell spacing. 
  // nuSum:         collisionalities added (self and cross species collisionalities). 
  // vMuMidMax:     maximum midpoint value of v-u. 
  // nuUSum[8]:     sum of bulk velocities times their respective collisionalities. 
  // nuVtSqSum[4]:  sum of thermal speeds squared time their respective collisionalities. 
  // fl/fr:         Distribution function in left/right cells 
  // outl/outr:     Incremented distribution function in left/right cells 
  double rdv = 1.0/dxvl[1]; 
  double rdv2L = 2.0/dxvl[1]; 
  double rdv2R = 2.0/dxvr[1]; 
  double rdvSq4L = 4.0/(dxvl[1]*dxvl[1]); 
  double rdvSq4R = 4.0/(dxvr[1]*dxvr[1]); 

  const double *sumNuUx = &nuUSum[0]; 

  double favg[32]; 
  favg[0] = 1*fr[0]+fl[0]; 
  favg[1] = 1*fr[1]+fl[1]; 
  favg[2] = -1*fr[2]+fl[2]; 
  favg[3] = 1*fr[3]+fl[3]; 
  favg[4] = -1*fr[4]+fl[4]; 
  favg[5] = 1*fr[5]+fl[5]; 
  favg[6] = -1*fr[6]+fl[6]; 
  favg[7] = 1*fr[7]+fl[7]; 
  favg[8] = 1*fr[8]+fl[8]; 
  favg[9] = 1*fr[9]+fl[9]; 
  favg[10] = -1*fr[10]+fl[10]; 
  favg[11] = -1*fr[11]+fl[11]; 
  favg[12] = 1*fr[12]+fl[12]; 
  favg[13] = 1*fr[13]+fl[13]; 
  favg[14] = 1*fr[14]+fl[14]; 
  favg[15] = 1*fr[15]+fl[15]; 
  favg[16] = -1*fr[16]+fl[16]; 
  favg[17] = 1*fr[17]+fl[17]; 
  favg[18] = -1*fr[18]+fl[18]; 
  favg[19] = 1*fr[19]+fl[19]; 
  favg[20] = -1*fr[20]+fl[20]; 
  favg[21] = 1*fr[21]+fl[21]; 
  favg[22] = -1*fr[22]+fl[22]; 
  favg[23] = -1*fr[23]+fl[23]; 
  favg[24] = -1*fr[24]+fl[24]; 
  favg[25] = 1*fr[25]+fl[25]; 
  favg[26] = -1*fr[26]+fl[26]; 
  favg[27] = 1*fr[27]+fl[27]; 
  favg[28] = -1*fr[28]+fl[28]; 
  favg[29] = -1*fr[29]+fl[29]; 
  favg[30] = -1*fr[30]+fl[30]; 
  favg[31] = -1*fr[31]+fl[31]; 

  double fjump[32]; 
  fjump[0] = nuSum*vMuMidMax*(fl[0]-(1*fr[0])); 
  fjump[1] = nuSum*vMuMidMax*(fl[1]-(1*fr[1])); 
  fjump[2] = nuSum*vMuMidMax*(fl[2]-(-1*fr[2])); 
  fjump[3] = nuSum*vMuMidMax*(fl[3]-(1*fr[3])); 
  fjump[4] = nuSum*vMuMidMax*(fl[4]-(-1*fr[4])); 
  fjump[5] = nuSum*vMuMidMax*(fl[5]-(1*fr[5])); 
  fjump[6] = nuSum*vMuMidMax*(fl[6]-(-1*fr[6])); 
  fjump[7] = nuSum*vMuMidMax*(fl[7]-(1*fr[7])); 
  fjump[8] = nuSum*vMuMidMax*(fl[8]-(1*fr[8])); 
  fjump[9] = nuSum*vMuMidMax*(fl[9]-(1*fr[9])); 
  fjump[10] = nuSum*vMuMidMax*(fl[10]-(-1*fr[10])); 
  fjump[11] = nuSum*vMuMidMax*(fl[11]-(-1*fr[11])); 
  fjump[12] = nuSum*vMuMidMax*(fl[12]-(1*fr[12])); 
  fjump[13] = nuSum*vMuMidMax*(fl[13]-(1*fr[13])); 
  fjump[14] = nuSum*vMuMidMax*(fl[14]-(1*fr[14])); 
  fjump[15] = nuSum*vMuMidMax*(fl[15]-(1*fr[15])); 
  fjump[16] = nuSum*vMuMidMax*(fl[16]-(-1*fr[16])); 
  fjump[17] = nuSum*vMuMidMax*(fl[17]-(1*fr[17])); 
  fjump[18] = nuSum*vMuMidMax*(fl[18]-(-1*fr[18])); 
  fjump[19] = nuSum*vMuMidMax*(fl[19]-(1*fr[19])); 
  fjump[20] = nuSum*vMuMidMax*(fl[20]-(-1*fr[20])); 
  fjump[21] = nuSum*vMuMidMax*(fl[21]-(1*fr[21])); 
  fjump[22] = nuSum*vMuMidMax*(fl[22]-(-1*fr[22])); 
  fjump[23] = nuSum*vMuMidMax*(fl[23]-(-1*fr[23])); 
  fjump[24] = nuSum*vMuMidMax*(fl[24]-(-1*fr[24])); 
  fjump[25] = nuSum*vMuMidMax*(fl[25]-(1*fr[25])); 
  fjump[26] = nuSum*vMuMidMax*(fl[26]-(-1*fr[26])); 
  fjump[27] = nuSum*vMuMidMax*(fl[27]-(1*fr[27])); 
  fjump[28] = nuSum*vMuMidMax*(fl[28]-(-1*fr[28])); 
  fjump[29] = nuSum*vMuMidMax*(fl[29]-(-1*fr[29])); 
  fjump[30] = nuSum*vMuMidMax*(fl[30]-(-1*fr[30])); 
  fjump[31] = nuSum*vMuMidMax*(fl[31]-(-1*fr[31])); 

  double alphaDrag[4]; 
  alphaDrag[0] = 1.414213562373095*wl[1]*nuSum+0.7071067811865475*dxvl[1]*nuSum-1.0*sumNuUx[0]; 
  alphaDrag[1] = -1.0*sumNuUx[1]; 
  alphaDrag[2] = -1.0*sumNuUx[2]; 
  alphaDrag[3] = -1.0*sumNuUx[3]; 

  double Ghat[32]; 
  for(unsigned short int i=0; i<32; ++i){ 
    Ghat[i]=0.0; 
  }; 

  Ghat[0] = ((-1.929292090055312*nuVtSqSum[1]*fr[24])-1.929292090055312*nuVtSqSum[1]*fl[24]-5.473078644031158*nuVtSqSum[3]*fr[23]-5.473078644031158*nuVtSqSum[3]*fl[23]-1.929292090055312*nuVtSqSum[0]*fr[18]-1.929292090055312*nuVtSqSum[0]*fl[18]+3.866990209613929*nuVtSqSum[3]*fr[17]-3.866990209613929*nuVtSqSum[3]*fl[17]+4.39754237117165*nuVtSqSum[1]*fr[12]-4.39754237117165*nuVtSqSum[1]*fl[12]-5.473078644031159*nuVtSqSum[2]*fr[11]-5.473078644031159*nuVtSqSum[2]*fl[11]+4.397542371171649*nuVtSqSum[0]*fr[8]-4.397542371171649*nuVtSqSum[0]*fl[8]+3.866990209613929*nuVtSqSum[2]*fr[7]-3.866990209613929*nuVtSqSum[2]*fl[7]-5.473078644031159*nuVtSqSum[1]*fr[4]-5.473078644031159*nuVtSqSum[1]*fl[4]-5.473078644031159*nuVtSqSum[0]*fr[2]-5.473078644031159*nuVtSqSum[0]*fl[2]+3.866990209613929*fr[1]*nuVtSqSum[1]-3.866990209613929*fl[1]*nuVtSqSum[1]+3.866990209613929*fr[0]*nuVtSqSum[0]-3.866990209613929*fl[0]*nuVtSqSum[0])*rdv+alphaDrag[1]*(0.9354143466934852*favg[24]+0.7905694150420948*favg[12]+0.6123724356957944*favg[4]+0.3535533905932737*favg[1])+alphaDrag[3]*(0.6123724356957942*favg[23]+0.3535533905932737*favg[17])-1.322875655532295*fjump[18]+alphaDrag[0]*(0.9354143466934851*favg[18]+0.7905694150420947*favg[8]+0.6123724356957944*favg[2]+0.3535533905932737*favg[0])+alphaDrag[2]*(0.6123724356957944*favg[11]+0.3535533905932737*favg[7])-1.118033988749895*fjump[8]-0.8660254037844386*fjump[2]-0.5*fjump[0]; 
  Ghat[1] = ((-1.72561130472653*nuVtSqSum[2]*fr[24])-1.929292090055312*nuVtSqSum[0]*fr[24]-1.72561130472653*nuVtSqSum[2]*fl[24]-1.929292090055312*nuVtSqSum[0]*fl[24]-4.80706006316676*nuVtSqSum[2]*fr[23]-4.80706006316676*nuVtSqSum[2]*fl[23]-1.929292090055312*nuVtSqSum[1]*fr[18]-1.929292090055312*nuVtSqSum[1]*fl[18]+3.396416424888148*nuVtSqSum[2]*fr[17]-3.396416424888148*nuVtSqSum[2]*fl[17]+3.933281470350169*nuVtSqSum[2]*fr[12]+4.39754237117165*nuVtSqSum[0]*fr[12]-3.933281470350169*nuVtSqSum[2]*fl[12]-4.39754237117165*nuVtSqSum[0]*fl[12]-4.807060063166761*nuVtSqSum[3]*fr[11]-4.89527035770242*nuVtSqSum[1]*fr[11]-4.807060063166761*nuVtSqSum[3]*fl[11]-4.89527035770242*nuVtSqSum[1]*fl[11]+4.397542371171649*nuVtSqSum[1]*fr[8]-4.397542371171649*nuVtSqSum[1]*fl[8]+3.396416424888148*nuVtSqSum[3]*fr[7]+3.458741190809164*nuVtSqSum[1]*fr[7]-3.396416424888148*nuVtSqSum[3]*fl[7]-3.458741190809164*nuVtSqSum[1]*fl[7]-4.89527035770242*nuVtSqSum[2]*fr[4]-5.473078644031159*nuVtSqSum[0]*fr[4]-4.89527035770242*nuVtSqSum[2]*fl[4]-5.473078644031159*nuVtSqSum[0]*fl[4]+3.458741190809164*fr[1]*nuVtSqSum[2]-3.458741190809164*fl[1]*nuVtSqSum[2]-5.473078644031159*nuVtSqSum[1]*fr[2]-5.473078644031159*nuVtSqSum[1]*fl[2]+3.866990209613929*fr[0]*nuVtSqSum[1]-3.866990209613929*fl[0]*nuVtSqSum[1]+3.866990209613929*nuVtSqSum[0]*fr[1]-3.866990209613929*nuVtSqSum[0]*fl[1])*rdv-1.322875655532295*fjump[24]+alphaDrag[0]*(0.9354143466934852*favg[24]+0.7905694150420948*favg[12]+0.6123724356957944*favg[4]+0.3535533905932737*favg[1])+alphaDrag[2]*(0.8366600265340755*favg[24]+0.5378528742004768*favg[23]+0.3105295017040592*favg[17]+0.7071067811865475*favg[12]+0.5477225575051661*favg[4]+0.3162277660168379*favg[1])+alphaDrag[1]*(0.9354143466934851*favg[18]+0.5477225575051661*favg[11]+0.7905694150420947*favg[8]+0.3162277660168379*favg[7]+0.6123724356957944*favg[2]+0.3535533905932737*favg[0])-1.118033988749895*fjump[12]+alphaDrag[3]*(0.5378528742004769*favg[11]+0.3105295017040592*favg[7])-0.8660254037844386*fjump[4]-0.5*fjump[1]; 
  Ghat[3] = ((-1.929292090055312*nuVtSqSum[1]*fr[30])-1.929292090055312*nuVtSqSum[1]*fl[30]-5.473078644031159*nuVtSqSum[3]*fr[29]-5.473078644031159*nuVtSqSum[3]*fl[29]-1.929292090055312*nuVtSqSum[0]*fr[26]-1.929292090055312*nuVtSqSum[0]*fl[26]+3.86699020961393*nuVtSqSum[3]*fr[25]-3.86699020961393*nuVtSqSum[3]*fl[25]+4.397542371171649*nuVtSqSum[1]*fr[21]-4.397542371171649*nuVtSqSum[1]*fl[21]-5.473078644031159*nuVtSqSum[2]*fr[20]-5.473078644031159*nuVtSqSum[2]*fl[20]+4.39754237117165*nuVtSqSum[0]*fr[14]-4.39754237117165*nuVtSqSum[0]*fl[14]+3.86699020961393*nuVtSqSum[2]*fr[13]-3.86699020961393*nuVtSqSum[2]*fl[13]-5.473078644031159*nuVtSqSum[1]*fr[10]-5.473078644031159*nuVtSqSum[1]*fl[10]-5.473078644031159*nuVtSqSum[0]*fr[6]-5.473078644031159*nuVtSqSum[0]*fl[6]+3.866990209613929*nuVtSqSum[1]*fr[5]-3.866990209613929*nuVtSqSum[1]*fl[5]+3.866990209613929*nuVtSqSum[0]*fr[3]-3.866990209613929*nuVtSqSum[0]*fl[3])*rdv+alphaDrag[1]*(0.9354143466934851*favg[30]+0.7905694150420947*favg[21]+0.6123724356957944*favg[10]+0.3535533905932737*favg[5])+alphaDrag[3]*(0.6123724356957944*favg[29]+0.3535533905932737*favg[25])-1.322875655532295*fjump[26]+alphaDrag[0]*(0.9354143466934852*favg[26]+0.7905694150420948*favg[14]+0.6123724356957944*favg[6]+0.3535533905932737*favg[3])+alphaDrag[2]*(0.6123724356957944*favg[20]+0.3535533905932737*favg[13])-1.118033988749895*fjump[14]-0.8660254037844386*fjump[6]-0.5*fjump[3]; 
  Ghat[5] = ((-1.72561130472653*nuVtSqSum[2]*fr[30])-1.929292090055312*nuVtSqSum[0]*fr[30]-1.72561130472653*nuVtSqSum[2]*fl[30]-1.929292090055312*nuVtSqSum[0]*fl[30]-4.807060063166761*nuVtSqSum[2]*fr[29]-4.807060063166761*nuVtSqSum[2]*fl[29]-1.929292090055312*nuVtSqSum[1]*fr[26]-1.929292090055312*nuVtSqSum[1]*fl[26]+3.396416424888148*nuVtSqSum[2]*fr[25]-3.396416424888148*nuVtSqSum[2]*fl[25]+3.933281470350169*nuVtSqSum[2]*fr[21]+4.397542371171649*nuVtSqSum[0]*fr[21]-3.933281470350169*nuVtSqSum[2]*fl[21]-4.397542371171649*nuVtSqSum[0]*fl[21]-4.807060063166761*nuVtSqSum[3]*fr[20]-4.89527035770242*nuVtSqSum[1]*fr[20]-4.807060063166761*nuVtSqSum[3]*fl[20]-4.89527035770242*nuVtSqSum[1]*fl[20]+4.39754237117165*nuVtSqSum[1]*fr[14]-4.39754237117165*nuVtSqSum[1]*fl[14]+3.396416424888148*nuVtSqSum[3]*fr[13]+3.458741190809164*nuVtSqSum[1]*fr[13]-3.396416424888148*nuVtSqSum[3]*fl[13]-3.458741190809164*nuVtSqSum[1]*fl[13]-4.89527035770242*nuVtSqSum[2]*fr[10]-5.473078644031159*nuVtSqSum[0]*fr[10]-4.89527035770242*nuVtSqSum[2]*fl[10]-5.473078644031159*nuVtSqSum[0]*fl[10]-5.473078644031159*nuVtSqSum[1]*fr[6]-5.473078644031159*nuVtSqSum[1]*fl[6]+3.458741190809164*nuVtSqSum[2]*fr[5]+3.866990209613929*nuVtSqSum[0]*fr[5]-3.458741190809164*nuVtSqSum[2]*fl[5]-3.866990209613929*nuVtSqSum[0]*fl[5]+3.866990209613929*nuVtSqSum[1]*fr[3]-3.866990209613929*nuVtSqSum[1]*fl[3])*rdv-1.322875655532295*fjump[30]+alphaDrag[0]*(0.9354143466934851*favg[30]+0.7905694150420947*favg[21]+0.6123724356957944*favg[10]+0.3535533905932737*favg[5])+alphaDrag[2]*(0.8366600265340755*favg[30]+0.537852874200477*favg[29]+0.3105295017040593*favg[25]+0.7071067811865475*favg[21]+0.5477225575051661*favg[10]+0.3162277660168379*favg[5])+alphaDrag[1]*(0.9354143466934852*favg[26]+0.5477225575051661*favg[20]+0.7905694150420948*favg[14]+0.3162277660168379*favg[13]+0.6123724356957944*favg[6]+0.3535533905932737*favg[3])-1.118033988749895*fjump[21]+alphaDrag[3]*(0.537852874200477*favg[20]+0.3105295017040593*favg[13])-0.8660254037844386*fjump[10]-0.5*fjump[5]; 
  Ghat[7] = ((-1.694516662281606*nuVtSqSum[3]*fr[24])-1.72561130472653*nuVtSqSum[1]*fr[24]-1.694516662281606*nuVtSqSum[3]*fl[24]-1.72561130472653*nuVtSqSum[1]*fl[24]-3.263513571801613*nuVtSqSum[3]*fr[23]-4.80706006316676*nuVtSqSum[1]*fr[23]-3.263513571801613*nuVtSqSum[3]*fl[23]-4.80706006316676*nuVtSqSum[1]*fl[23]-1.929292090055312*nuVtSqSum[2]*fr[18]-1.929292090055312*nuVtSqSum[2]*fl[18]+2.305827460539443*nuVtSqSum[3]*fr[17]+3.396416424888148*nuVtSqSum[1]*fr[17]-2.305827460539443*nuVtSqSum[3]*fl[17]-3.396416424888148*nuVtSqSum[1]*fl[17]+3.86240572873861*nuVtSqSum[3]*fr[12]+3.933281470350169*nuVtSqSum[1]*fr[12]-3.86240572873861*nuVtSqSum[3]*fl[12]-3.933281470350169*nuVtSqSum[1]*fl[12]-3.496621684073157*nuVtSqSum[2]*fr[11]-5.473078644031159*nuVtSqSum[0]*fr[11]-3.496621684073157*nuVtSqSum[2]*fl[11]-5.473078644031159*nuVtSqSum[0]*fl[11]+4.397542371171649*nuVtSqSum[2]*fr[8]-4.397542371171649*nuVtSqSum[2]*fl[8]+2.470529422006546*nuVtSqSum[2]*fr[7]+3.866990209613929*nuVtSqSum[0]*fr[7]-2.470529422006546*nuVtSqSum[2]*fl[7]-3.866990209613929*nuVtSqSum[0]*fl[7]-4.807060063166761*nuVtSqSum[3]*fr[4]-4.89527035770242*nuVtSqSum[1]*fr[4]-4.807060063166761*nuVtSqSum[3]*fl[4]-4.89527035770242*nuVtSqSum[1]*fl[4]+3.396416424888148*fr[1]*nuVtSqSum[3]-3.396416424888148*fl[1]*nuVtSqSum[3]-5.473078644031159*fr[2]*nuVtSqSum[2]-5.473078644031159*fl[2]*nuVtSqSum[2]+3.866990209613929*fr[0]*nuVtSqSum[2]-3.866990209613929*fl[0]*nuVtSqSum[2]+3.458741190809164*fr[1]*nuVtSqSum[1]-3.458741190809164*fl[1]*nuVtSqSum[1])*rdv+alphaDrag[1]*(0.8366600265340755*favg[24]+0.5378528742004768*favg[23]+0.3105295017040592*favg[17]+0.7071067811865475*favg[12]+0.5477225575051661*favg[4]+0.3162277660168379*favg[1])+alphaDrag[3]*(0.8215838362577488*favg[24]+0.3651483716701107*favg[23]+0.210818510677892*favg[17]+0.6943650748294133*favg[12]+0.537852874200477*favg[4]+0.3105295017040592*favg[1])+alphaDrag[2]*(0.9354143466934851*favg[18]+0.3912303982179757*favg[11]+0.7905694150420947*favg[8]+0.2258769757263128*favg[7]+0.6123724356957944*favg[2]+0.3535533905932737*favg[0])-0.8660254037844387*fjump[11]+alphaDrag[0]*(0.6123724356957944*favg[11]+0.3535533905932737*favg[7])-0.5*fjump[7]; 
  Ghat[9] = ((-5.473078644031159*nuVtSqSum[1]*fr[22])-5.473078644031159*nuVtSqSum[1]*fl[22]-5.473078644031159*nuVtSqSum[0]*fr[16]-5.473078644031159*nuVtSqSum[0]*fl[16]+3.86699020961393*nuVtSqSum[1]*fr[15]-3.86699020961393*nuVtSqSum[1]*fl[15]+3.866990209613929*nuVtSqSum[0]*fr[9]-3.866990209613929*nuVtSqSum[0]*fl[9])*rdv+alphaDrag[1]*(0.6123724356957944*favg[22]+0.3535533905932737*favg[15])-0.8660254037844387*fjump[16]+alphaDrag[0]*(0.6123724356957944*favg[16]+0.3535533905932737*favg[9])-0.5*fjump[9]; 
  Ghat[13] = ((-1.694516662281607*nuVtSqSum[3]*fr[30])-1.72561130472653*nuVtSqSum[1]*fr[30]-1.694516662281607*nuVtSqSum[3]*fl[30]-1.72561130472653*nuVtSqSum[1]*fl[30]-3.263513571801613*nuVtSqSum[3]*fr[29]-4.807060063166761*nuVtSqSum[1]*fr[29]-3.263513571801613*nuVtSqSum[3]*fl[29]-4.807060063166761*nuVtSqSum[1]*fl[29]-1.929292090055312*nuVtSqSum[2]*fr[26]-1.929292090055312*nuVtSqSum[2]*fl[26]+2.305827460539442*nuVtSqSum[3]*fr[25]+3.396416424888147*nuVtSqSum[1]*fr[25]-2.305827460539442*nuVtSqSum[3]*fl[25]-3.396416424888147*nuVtSqSum[1]*fl[25]+3.86240572873861*nuVtSqSum[3]*fr[21]+3.933281470350169*nuVtSqSum[1]*fr[21]-3.86240572873861*nuVtSqSum[3]*fl[21]-3.933281470350169*nuVtSqSum[1]*fl[21]-3.496621684073157*nuVtSqSum[2]*fr[20]-5.473078644031159*nuVtSqSum[0]*fr[20]-3.496621684073157*nuVtSqSum[2]*fl[20]-5.473078644031159*nuVtSqSum[0]*fl[20]+4.397542371171649*nuVtSqSum[2]*fr[14]-4.397542371171649*nuVtSqSum[2]*fl[14]+2.470529422006546*nuVtSqSum[2]*fr[13]+3.866990209613929*nuVtSqSum[0]*fr[13]-2.470529422006546*nuVtSqSum[2]*fl[13]-3.866990209613929*nuVtSqSum[0]*fl[13]-4.807060063166761*nuVtSqSum[3]*fr[10]-4.89527035770242*nuVtSqSum[1]*fr[10]-4.807060063166761*nuVtSqSum[3]*fl[10]-4.89527035770242*nuVtSqSum[1]*fl[10]-5.473078644031159*nuVtSqSum[2]*fr[6]-5.473078644031159*nuVtSqSum[2]*fl[6]+3.396416424888148*nuVtSqSum[3]*fr[5]+3.458741190809164*nuVtSqSum[1]*fr[5]-3.396416424888148*nuVtSqSum[3]*fl[5]-3.458741190809164*nuVtSqSum[1]*fl[5]+3.86699020961393*nuVtSqSum[2]*fr[3]-3.86699020961393*nuVtSqSum[2]*fl[3])*rdv+alphaDrag[1]*(0.8366600265340757*favg[30]+0.5378528742004769*favg[29]+0.3105295017040593*favg[25]+0.7071067811865475*favg[21]+0.5477225575051661*favg[10]+0.3162277660168379*favg[5])+alphaDrag[3]*(0.821583836257749*favg[30]+0.3651483716701107*favg[29]+0.2108185106778919*favg[25]+0.6943650748294133*favg[21]+0.5378528742004769*favg[10]+0.3105295017040593*favg[5])+alphaDrag[2]*(0.9354143466934851*favg[26]+0.3912303982179757*favg[20]+0.7905694150420947*favg[14]+0.2258769757263128*favg[13]+0.6123724356957944*favg[6]+0.3535533905932737*favg[3])-0.8660254037844387*fjump[20]+alphaDrag[0]*(0.6123724356957944*favg[20]+0.3535533905932737*favg[13])-0.5*fjump[13]; 
  Ghat[15] = ((-4.89527035770242*nuVtSqSum[2]*fr[22])-5.473078644031159*nuVtSqSum[0]*fr[22]-4.89527035770242*nuVtSqSum[2]*fl[22]-5.473078644031159*nuVtSqSum[0]*fl[22]-5.473078644031159*nuVtSqSum[1]*fr[16]-5.473078644031159*nuVtSqSum[1]*fl[16]+3.458741190809164*nuVtSqSum[2]*fr[15]+3.866990209613929*nuVtSqSum[0]*fr[15]-3.458741190809164*nuVtSqSum[2]*fl[15]-3.866990209613929*nuVtSqSum[0]*fl[15]+3.86699020961393*nuVtSqSum[1]*fr[9]-3.86699020961393*nuVtSqSum[1]*fl[9])*rdv-0.8660254037844387*fjump[22]+alphaDrag[0]*(0.6123724356957944*favg[22]+0.3535533905932737*favg[15])+alphaDrag[2]*(0.5477225575051661*favg[22]+0.3162277660168379*favg[15])+alphaDrag[1]*(0.6123724356957944*favg[16]+0.3535533905932737*favg[9])-0.5*fjump[15]; 
  Ghat[17] = ((-1.694516662281606*nuVtSqSum[2]*fr[24])-1.694516662281606*nuVtSqSum[2]*fl[24]-3.263513571801613*nuVtSqSum[2]*fr[23]-5.473078644031158*nuVtSqSum[0]*fr[23]-3.263513571801613*nuVtSqSum[2]*fl[23]-5.473078644031158*nuVtSqSum[0]*fl[23]-1.929292090055312*nuVtSqSum[3]*fr[18]-1.929292090055312*nuVtSqSum[3]*fl[18]+2.305827460539443*nuVtSqSum[2]*fr[17]+3.866990209613929*nuVtSqSum[0]*fr[17]-2.305827460539443*nuVtSqSum[2]*fl[17]-3.866990209613929*nuVtSqSum[0]*fl[17]+3.86240572873861*nuVtSqSum[2]*fr[12]-3.86240572873861*nuVtSqSum[2]*fl[12]-3.263513571801613*nuVtSqSum[3]*fr[11]-4.807060063166761*nuVtSqSum[1]*fr[11]-3.263513571801613*nuVtSqSum[3]*fl[11]-4.807060063166761*nuVtSqSum[1]*fl[11]+4.397542371171649*nuVtSqSum[3]*fr[8]-4.397542371171649*nuVtSqSum[3]*fl[8]+2.305827460539443*nuVtSqSum[3]*fr[7]+3.396416424888148*nuVtSqSum[1]*fr[7]-2.305827460539443*nuVtSqSum[3]*fl[7]-3.396416424888148*nuVtSqSum[1]*fl[7]-4.807060063166761*nuVtSqSum[2]*fr[4]-4.807060063166761*nuVtSqSum[2]*fl[4]-5.473078644031159*fr[2]*nuVtSqSum[3]-5.473078644031159*fl[2]*nuVtSqSum[3]+3.866990209613929*fr[0]*nuVtSqSum[3]-3.866990209613929*fl[0]*nuVtSqSum[3]+3.396416424888148*fr[1]*nuVtSqSum[2]-3.396416424888148*fl[1]*nuVtSqSum[2])*rdv+alphaDrag[2]*(0.8215838362577488*favg[24]+0.3651483716701107*favg[23]+0.210818510677892*favg[17]+0.6943650748294133*favg[12]+0.537852874200477*favg[4]+0.3105295017040592*favg[1])-0.8660254037844386*fjump[23]+alphaDrag[0]*(0.6123724356957942*favg[23]+0.3535533905932737*favg[17])+alphaDrag[3]*(0.9354143466934851*favg[18]+0.3651483716701107*favg[11]+0.7905694150420947*favg[8]+0.210818510677892*favg[7]+0.6123724356957944*favg[2]+0.3535533905932737*favg[0])-0.5*fjump[17]+alphaDrag[1]*(0.5378528742004769*favg[11]+0.3105295017040592*favg[7]); 
  Ghat[19] = ((-5.473078644031159*nuVtSqSum[1]*fr[31])-5.473078644031159*nuVtSqSum[1]*fl[31]-5.473078644031158*nuVtSqSum[0]*fr[28]-5.473078644031158*nuVtSqSum[0]*fl[28]+3.86699020961393*nuVtSqSum[1]*fr[27]-3.86699020961393*nuVtSqSum[1]*fl[27]+3.866990209613929*nuVtSqSum[0]*fr[19]-3.866990209613929*nuVtSqSum[0]*fl[19])*rdv+alphaDrag[1]*(0.6123724356957944*favg[31]+0.3535533905932737*favg[27])-0.8660254037844386*fjump[28]+alphaDrag[0]*(0.6123724356957942*favg[28]+0.3535533905932737*favg[19])-0.5*fjump[19]; 
  Ghat[25] = ((-1.694516662281606*nuVtSqSum[2]*fr[30])-1.694516662281606*nuVtSqSum[2]*fl[30]-3.263513571801613*nuVtSqSum[2]*fr[29]-5.473078644031158*nuVtSqSum[0]*fr[29]-3.263513571801613*nuVtSqSum[2]*fl[29]-5.473078644031158*nuVtSqSum[0]*fl[29]-1.929292090055312*nuVtSqSum[3]*fr[26]-1.929292090055312*nuVtSqSum[3]*fl[26]+2.305827460539443*nuVtSqSum[2]*fr[25]+3.866990209613929*nuVtSqSum[0]*fr[25]-2.305827460539443*nuVtSqSum[2]*fl[25]-3.866990209613929*nuVtSqSum[0]*fl[25]+3.86240572873861*nuVtSqSum[2]*fr[21]-3.86240572873861*nuVtSqSum[2]*fl[21]-3.263513571801613*nuVtSqSum[3]*fr[20]-4.80706006316676*nuVtSqSum[1]*fr[20]-3.263513571801613*nuVtSqSum[3]*fl[20]-4.80706006316676*nuVtSqSum[1]*fl[20]+4.397542371171649*nuVtSqSum[3]*fr[14]-4.397542371171649*nuVtSqSum[3]*fl[14]+2.305827460539442*nuVtSqSum[3]*fr[13]+3.396416424888147*nuVtSqSum[1]*fr[13]-2.305827460539442*nuVtSqSum[3]*fl[13]-3.396416424888147*nuVtSqSum[1]*fl[13]-4.80706006316676*nuVtSqSum[2]*fr[10]-4.80706006316676*nuVtSqSum[2]*fl[10]-5.473078644031158*nuVtSqSum[3]*fr[6]-5.473078644031158*nuVtSqSum[3]*fl[6]+3.396416424888148*nuVtSqSum[2]*fr[5]-3.396416424888148*nuVtSqSum[2]*fl[5]+3.86699020961393*fr[3]*nuVtSqSum[3]-3.86699020961393*fl[3]*nuVtSqSum[3])*rdv+alphaDrag[2]*(0.8215838362577488*favg[30]+0.3651483716701107*favg[29]+0.210818510677892*favg[25]+0.6943650748294133*favg[21]+0.5378528742004768*favg[10]+0.3105295017040593*favg[5])-0.8660254037844386*fjump[29]+alphaDrag[0]*(0.6123724356957942*favg[29]+0.3535533905932737*favg[25])+alphaDrag[3]*(0.9354143466934851*favg[26]+0.3651483716701107*favg[20]+0.7905694150420945*favg[14]+0.2108185106778919*favg[13]+0.6123724356957942*favg[6]+0.3535533905932737*favg[3])-0.5*fjump[25]+alphaDrag[1]*(0.5378528742004768*favg[20]+0.3105295017040593*favg[13]); 
  Ghat[27] = ((-4.895270357702419*nuVtSqSum[2]*fr[31])-5.473078644031158*nuVtSqSum[0]*fr[31]-4.895270357702419*nuVtSqSum[2]*fl[31]-5.473078644031158*nuVtSqSum[0]*fl[31]-5.473078644031159*nuVtSqSum[1]*fr[28]-5.473078644031159*nuVtSqSum[1]*fl[28]+3.458741190809164*nuVtSqSum[2]*fr[27]+3.866990209613929*nuVtSqSum[0]*fr[27]-3.458741190809164*nuVtSqSum[2]*fl[27]-3.866990209613929*nuVtSqSum[0]*fl[27]+3.86699020961393*nuVtSqSum[1]*fr[19]-3.86699020961393*nuVtSqSum[1]*fl[19])*rdv-0.8660254037844386*fjump[31]+alphaDrag[0]*(0.6123724356957942*favg[31]+0.3535533905932737*favg[27])+alphaDrag[2]*(0.547722557505166*favg[31]+0.3162277660168379*favg[27])+alphaDrag[1]*(0.6123724356957944*favg[28]+0.3535533905932737*favg[19])-0.5*fjump[27]; 

  double incr1[32]; 
  incr1[0] = -0.5*Ghat[0]; 
  incr1[1] = -0.5*Ghat[1]; 
  incr1[2] = 0.8660254037844386*Ghat[0]; 
  incr1[3] = -0.5*Ghat[3]; 
  incr1[4] = 0.8660254037844386*Ghat[1]; 
  incr1[5] = -0.5*Ghat[5]; 
  incr1[6] = 0.8660254037844386*Ghat[3]; 
  incr1[7] = -0.5*Ghat[7]; 
  incr1[8] = -1.118033988749895*Ghat[0]; 
  incr1[9] = -0.5*Ghat[9]; 
  incr1[10] = 0.8660254037844386*Ghat[5]; 
  incr1[11] = 0.8660254037844387*Ghat[7]; 
  incr1[12] = -1.118033988749895*Ghat[1]; 
  incr1[13] = -0.5*Ghat[13]; 
  incr1[14] = -1.118033988749895*Ghat[3]; 
  incr1[15] = -0.5*Ghat[15]; 
  incr1[16] = 0.8660254037844387*Ghat[9]; 
  incr1[17] = -0.5*Ghat[17]; 
  incr1[18] = 1.322875655532295*Ghat[0]; 
  incr1[19] = -0.5*Ghat[19]; 
  incr1[20] = 0.8660254037844387*Ghat[13]; 
  incr1[21] = -1.118033988749895*Ghat[5]; 
  incr1[22] = 0.8660254037844387*Ghat[15]; 
  incr1[23] = 0.8660254037844386*Ghat[17]; 
  incr1[24] = 1.322875655532295*Ghat[1]; 
  incr1[25] = -0.5*Ghat[25]; 
  incr1[26] = 1.322875655532295*Ghat[3]; 
  incr1[27] = -0.5*Ghat[27]; 
  incr1[28] = 0.8660254037844386*Ghat[19]; 
  incr1[29] = 0.8660254037844386*Ghat[25]; 
  incr1[30] = 1.322875655532295*Ghat[5]; 
  incr1[31] = 0.8660254037844386*Ghat[27]; 

  double incr2[32]; 
  incr2[2] = nuVtSqSum[1]*((-0.2314550249431378*fr[24])+0.2314550249431378*fl[24]+0.4279082480509107*(fr[12]+fl[12])-0.4640388251536715*fr[4]+0.4640388251536715*fl[4]+0.3061862178478971*(fr[1]+fl[1]))+nuVtSqSum[3]*((-0.4640388251536714*fr[23])+0.4640388251536714*fl[23]+0.3061862178478971*(fr[17]+fl[17]))+nuVtSqSum[0]*((-0.2314550249431378*fr[18])+0.2314550249431378*fl[18]+0.4279082480509108*(fr[8]+fl[8])-0.4640388251536715*fr[2]+0.4640388251536715*fl[2]+0.3061862178478971*(fr[0]+fl[0]))+nuVtSqSum[2]*((-0.4640388251536715*fr[11])+0.4640388251536715*fl[11]+0.3061862178478971*(fr[7]+fl[7])); 
  incr2[4] = nuVtSqSum[2]*((-0.2070196678027062*fr[24])+0.2070196678027062*fl[24]-0.4075699709865775*fr[23]+0.4075699709865775*fl[23]+0.2689264371002384*(fr[17]+fl[17])+0.3827327723098714*(fr[12]+fl[12])-0.4150489428970995*fr[4]+0.4150489428970995*fl[4]+0.273861278752583*(fr[1]+fl[1]))+nuVtSqSum[0]*((-0.2314550249431378*fr[24])+0.2314550249431378*fl[24]+0.4279082480509107*(fr[12]+fl[12])-0.4640388251536715*fr[4]+0.4640388251536715*fl[4]+0.3061862178478971*(fr[1]+fl[1]))+nuVtSqSum[1]*((-0.2314550249431378*fr[18])+0.2314550249431378*fl[18]-0.4150489428970995*fr[11]+0.4150489428970995*fl[11]+0.4279082480509108*(fr[8]+fl[8])+0.273861278752583*(fr[7]+fl[7])-0.4640388251536715*fr[2]+0.4640388251536715*fl[2]+0.3061862178478971*(fr[0]+fl[0]))+nuVtSqSum[3]*((-0.4075699709865777*fr[11])+0.4075699709865777*fl[11]+0.2689264371002384*(fr[7]+fl[7])); 
  incr2[6] = nuVtSqSum[1]*((-0.2314550249431378*fr[30])+0.2314550249431378*fl[30]+0.4279082480509108*(fr[21]+fl[21])-0.4640388251536715*fr[10]+0.4640388251536715*fl[10]+0.3061862178478971*(fr[5]+fl[5]))+nuVtSqSum[3]*((-0.4640388251536715*fr[29])+0.4640388251536715*fl[29]+0.3061862178478971*(fr[25]+fl[25]))+nuVtSqSum[0]*((-0.2314550249431378*fr[26])+0.2314550249431378*fl[26]+0.4279082480509107*(fr[14]+fl[14])-0.4640388251536715*fr[6]+0.4640388251536715*fl[6]+0.3061862178478971*(fr[3]+fl[3]))+nuVtSqSum[2]*((-0.4640388251536715*fr[20])+0.4640388251536715*fl[20]+0.3061862178478971*(fr[13]+fl[13])); 
  incr2[8] = nuVtSqSum[1]*(0.8964214570007949*fr[24]-0.8964214570007949*fl[24]-1.65728151840597*(fr[12]+fl[12])+1.797214641813825*fr[4]-1.797214641813825*fl[4]-1.185854122563142*(fr[1]+fl[1]))+nuVtSqSum[3]*(1.797214641813825*fr[23]-1.797214641813825*fl[23]-1.185854122563142*(fr[17]+fl[17]))+nuVtSqSum[0]*(0.896421457000795*fr[18]-0.896421457000795*fl[18]-1.657281518405969*(fr[8]+fl[8])+1.797214641813825*fr[2]-1.797214641813825*fl[2]-1.185854122563142*(fr[0]+fl[0]))+nuVtSqSum[2]*(1.797214641813825*fr[11]-1.797214641813825*fl[11]-1.185854122563142*(fr[7]+fl[7])); 
  incr2[10] = nuVtSqSum[2]*((-0.2070196678027062*fr[30])+0.2070196678027062*fl[30]-0.4075699709865775*fr[29]+0.4075699709865775*fl[29]+0.2689264371002383*(fr[25]+fl[25])+0.3827327723098713*(fr[21]+fl[21])-0.4150489428970995*fr[10]+0.4150489428970995*fl[10]+0.273861278752583*(fr[5]+fl[5]))+nuVtSqSum[0]*((-0.2314550249431378*fr[30])+0.2314550249431378*fl[30]+0.4279082480509108*(fr[21]+fl[21])-0.4640388251536715*fr[10]+0.4640388251536715*fl[10]+0.3061862178478971*(fr[5]+fl[5]))+nuVtSqSum[1]*((-0.2314550249431378*fr[26])+0.2314550249431378*fl[26]-0.4150489428970995*fr[20]+0.4150489428970995*fl[20]+0.4279082480509107*(fr[14]+fl[14])+0.273861278752583*(fr[13]+fl[13])-0.4640388251536715*fr[6]+0.4640388251536715*fl[6]+0.3061862178478971*(fr[3]+fl[3]))+nuVtSqSum[3]*((-0.4075699709865775*fr[20])+0.4075699709865775*fl[20]+0.2689264371002384*(fr[13]+fl[13])); 
  incr2[11] = nuVtSqSum[3]*((-0.2032892781536815*fr[24])+0.2032892781536815*fl[24]-0.276699295264733*fr[23]+0.276699295264733*fl[23]+0.1825741858350553*(fr[17]+fl[17])+0.3758361214393465*(fr[12]+fl[12])-0.4075699709865777*fr[4]+0.4075699709865777*fl[4]+0.2689264371002384*(fr[1]+fl[1]))+nuVtSqSum[1]*((-0.2070196678027063*fr[24])+0.2070196678027063*fl[24]-0.4075699709865777*fr[23]+0.4075699709865777*fl[23]+0.2689264371002384*(fr[17]+fl[17])+0.3827327723098713*(fr[12]+fl[12])-0.4150489428970995*fr[4]+0.4150489428970995*fl[4]+0.273861278752583*(fr[1]+fl[1]))+nuVtSqSum[2]*((-0.2314550249431378*fr[18])+0.2314550249431378*fl[18]-0.2964635306407854*fr[11]+0.2964635306407854*fl[11]+0.4279082480509108*(fr[8]+fl[8])+0.1956151991089878*(fr[7]+fl[7])-0.4640388251536715*fr[2]+0.4640388251536715*fl[2]+0.3061862178478971*(fr[0]+fl[0]))+nuVtSqSum[0]*((-0.4640388251536715*fr[11])+0.4640388251536715*fl[11]+0.3061862178478971*(fr[7]+fl[7])); 
  incr2[12] = nuVtSqSum[0]*(0.8964214570007949*fr[24]-0.8964214570007949*fl[24]-1.657281518405969*(fr[12]+fl[12])+1.797214641813825*fr[4]-1.797214641813825*fl[4]-1.185854122563142*(fr[1]+fl[1]))+nuVtSqSum[2]*(0.8017837257372731*fr[24]-0.8017837257372731*fl[24]+1.578511710045255*fr[23]-1.578511710045255*fl[23]-1.04154761224412*(fr[17]+fl[17])-1.482317653203927*(fr[12]+fl[12])+1.60747764370146*fr[4]-1.60747764370146*fl[4]-1.060660171779821*(fr[1]+fl[1]))+nuVtSqSum[1]*(0.8964214570007949*fr[18]-0.8964214570007949*fl[18]+1.60747764370146*fr[11]-1.60747764370146*fl[11]-1.65728151840597*(fr[8]+fl[8])-1.060660171779821*(fr[7]+fl[7])+1.797214641813825*fr[2]-1.797214641813825*fl[2]-1.185854122563142*(fr[0]+fl[0]))+nuVtSqSum[3]*(1.578511710045255*fr[11]-1.578511710045255*fl[11]-1.04154761224412*(fr[7]+fl[7])); 
  incr2[14] = nuVtSqSum[1]*(0.8964214570007949*fr[30]-0.8964214570007949*fl[30]-1.65728151840597*(fr[21]+fl[21])+1.797214641813825*fr[10]-1.797214641813825*fl[10]-1.185854122563142*(fr[5]+fl[5]))+nuVtSqSum[3]*(1.797214641813825*fr[29]-1.797214641813825*fl[29]-1.185854122563141*(fr[25]+fl[25]))+nuVtSqSum[0]*(0.8964214570007949*fr[26]-0.8964214570007949*fl[26]-1.657281518405969*(fr[14]+fl[14])+1.797214641813825*fr[6]-1.797214641813825*fl[6]-1.185854122563142*(fr[3]+fl[3]))+nuVtSqSum[2]*(1.797214641813825*fr[20]-1.797214641813825*fl[20]-1.185854122563142*(fr[13]+fl[13])); 
  incr2[16] = nuVtSqSum[1]*((-0.4640388251536715*fr[22])+0.4640388251536715*fl[22]+0.3061862178478971*(fr[15]+fl[15]))+nuVtSqSum[0]*((-0.4640388251536715*fr[16])+0.4640388251536715*fl[16]+0.3061862178478971*(fr[9]+fl[9])); 
  incr2[18] = nuVtSqSum[1]*((-2.121320343559642*fr[24])+2.121320343559642*fl[24]+3.921843874378477*(fr[12]+fl[12])-4.252986083330156*fr[4]+4.252986083330156*fl[4]+2.806243040080455*(fr[1]+fl[1]))+nuVtSqSum[3]*((-4.252986083330155*fr[23])+4.252986083330155*fl[23]+2.806243040080455*(fr[17]+fl[17]))+nuVtSqSum[0]*((-2.121320343559642*fr[18])+2.121320343559642*fl[18]+3.921843874378478*(fr[8]+fl[8])-4.252986083330156*fr[2]+4.252986083330156*fl[2]+2.806243040080455*(fr[0]+fl[0]))+nuVtSqSum[2]*((-4.252986083330157*fr[11])+4.252986083330157*fl[11]+2.806243040080455*(fr[7]+fl[7])); 
  incr2[20] = nuVtSqSum[3]*((-0.2032892781536815*fr[30])+0.2032892781536815*fl[30]-0.2766992952647331*fr[29]+0.2766992952647331*fl[29]+0.1825741858350553*(fr[25]+fl[25])+0.3758361214393465*(fr[21]+fl[21])-0.4075699709865775*fr[10]+0.4075699709865775*fl[10]+0.2689264371002384*(fr[5]+fl[5]))+nuVtSqSum[1]*((-0.2070196678027062*fr[30])+0.2070196678027062*fl[30]-0.4075699709865775*fr[29]+0.4075699709865775*fl[29]+0.2689264371002383*(fr[25]+fl[25])+0.3827327723098713*(fr[21]+fl[21])-0.4150489428970995*fr[10]+0.4150489428970995*fl[10]+0.273861278752583*(fr[5]+fl[5]))+nuVtSqSum[2]*((-0.2314550249431378*fr[26])+0.2314550249431378*fl[26]-0.2964635306407854*fr[20]+0.2964635306407854*fl[20]+0.4279082480509108*(fr[14]+fl[14])+0.1956151991089878*(fr[13]+fl[13])-0.4640388251536715*fr[6]+0.4640388251536715*fl[6]+0.3061862178478971*(fr[3]+fl[3]))+nuVtSqSum[0]*((-0.4640388251536715*fr[20])+0.4640388251536715*fl[20]+0.3061862178478971*(fr[13]+fl[13])); 
  incr2[21] = nuVtSqSum[0]*(0.896421457000795*fr[30]-0.896421457000795*fl[30]-1.657281518405969*(fr[21]+fl[21])+1.797214641813825*fr[10]-1.797214641813825*fl[10]-1.185854122563142*(fr[5]+fl[5]))+nuVtSqSum[2]*(0.801783725737273*fr[30]-0.801783725737273*fl[30]+1.578511710045255*fr[29]-1.578511710045255*fl[29]-1.04154761224412*(fr[25]+fl[25])-1.482317653203927*(fr[21]+fl[21])+1.60747764370146*fr[10]-1.60747764370146*fl[10]-1.060660171779821*(fr[5]+fl[5]))+nuVtSqSum[1]*(0.8964214570007949*fr[26]-0.8964214570007949*fl[26]+1.60747764370146*fr[20]-1.60747764370146*fl[20]-1.65728151840597*(fr[14]+fl[14])-1.060660171779821*(fr[13]+fl[13])+1.797214641813825*fr[6]-1.797214641813825*fl[6]-1.185854122563142*(fr[3]+fl[3]))+nuVtSqSum[3]*(1.578511710045255*fr[20]-1.578511710045255*fl[20]-1.04154761224412*(fr[13]+fl[13])); 
  incr2[22] = nuVtSqSum[2]*((-0.4150489428970995*fr[22])+0.4150489428970995*fl[22]+0.273861278752583*(fr[15]+fl[15]))+nuVtSqSum[0]*((-0.4640388251536715*fr[22])+0.4640388251536715*fl[22]+0.3061862178478971*(fr[15]+fl[15]))+nuVtSqSum[1]*((-0.4640388251536715*fr[16])+0.4640388251536715*fl[16]+0.3061862178478971*(fr[9]+fl[9])); 
  incr2[23] = nuVtSqSum[2]*((-0.2032892781536815*fr[24])+0.2032892781536815*fl[24]-0.2766992952647331*fr[23]+0.2766992952647331*fl[23]+0.1825741858350553*(fr[17]+fl[17])+0.3758361214393465*(fr[12]+fl[12])-0.4075699709865775*fr[4]+0.4075699709865775*fl[4]+0.2689264371002383*(fr[1]+fl[1]))+nuVtSqSum[0]*((-0.4640388251536715*fr[23])+0.4640388251536715*fl[23]+0.3061862178478971*(fr[17]+fl[17]))+nuVtSqSum[3]*((-0.2314550249431378*fr[18])+0.2314550249431378*fl[18]-0.276699295264733*fr[11]+0.276699295264733*fl[11]+0.4279082480509108*(fr[8]+fl[8])+0.1825741858350553*(fr[7]+fl[7])-0.4640388251536714*fr[2]+0.4640388251536714*fl[2]+0.3061862178478971*(fr[0]+fl[0]))+nuVtSqSum[1]*((-0.4075699709865777*fr[11])+0.4075699709865777*fl[11]+0.2689264371002383*(fr[7]+fl[7])); 
  incr2[24] = nuVtSqSum[2]*((-1.897366596101028*fr[24])+1.897366596101028*fl[24]-3.735440486073895*fr[23]+3.735440486073895*fl[23]+2.464751508773247*(fr[17]+fl[17])+3.507803800100569*(fr[12]+fl[12])-3.803986395874725*fr[4]+3.803986395874725*fl[4]+2.509980079602226*(fr[1]+fl[1]))+nuVtSqSum[0]*((-2.121320343559642*fr[24])+2.121320343559642*fl[24]+3.921843874378477*(fr[12]+fl[12])-4.252986083330155*fr[4]+4.252986083330155*fl[4]+2.806243040080455*(fr[1]+fl[1]))+nuVtSqSum[1]*((-2.121320343559642*fr[18])+2.121320343559642*fl[18]-3.803986395874726*fr[11]+3.803986395874726*fl[11]+3.921843874378477*(fr[8]+fl[8])+2.509980079602226*(fr[7]+fl[7])-4.252986083330155*fr[2]+4.252986083330155*fl[2]+2.806243040080455*(fr[0]+fl[0]))+nuVtSqSum[3]*((-3.735440486073896*fr[11])+3.735440486073896*fl[11]+2.464751508773247*(fr[7]+fl[7])); 
  incr2[26] = nuVtSqSum[1]*((-2.121320343559642*fr[30])+2.121320343559642*fl[30]+3.921843874378477*(fr[21]+fl[21])-4.252986083330155*fr[10]+4.252986083330155*fl[10]+2.806243040080455*(fr[5]+fl[5]))+nuVtSqSum[3]*((-4.252986083330155*fr[29])+4.252986083330155*fl[29]+2.806243040080455*(fr[25]+fl[25]))+nuVtSqSum[0]*((-2.121320343559642*fr[26])+2.121320343559642*fl[26]+3.921843874378477*(fr[14]+fl[14])-4.252986083330155*fr[6]+4.252986083330155*fl[6]+2.806243040080455*(fr[3]+fl[3]))+nuVtSqSum[2]*((-4.252986083330155*fr[20])+4.252986083330155*fl[20]+2.806243040080455*(fr[13]+fl[13])); 
  incr2[28] = nuVtSqSum[1]*((-0.4640388251536714*fr[31])+0.4640388251536714*fl[31]+0.3061862178478971*(fr[27]+fl[27]))+nuVtSqSum[0]*((-0.4640388251536715*fr[28])+0.4640388251536715*fl[28]+0.3061862178478971*(fr[19]+fl[19])); 
  incr2[29] = nuVtSqSum[2]*((-0.2032892781536815*fr[30])+0.2032892781536815*fl[30]-0.2766992952647331*fr[29]+0.2766992952647331*fl[29]+0.1825741858350553*(fr[25]+fl[25])+0.3758361214393465*(fr[21]+fl[21])-0.4075699709865775*fr[10]+0.4075699709865775*fl[10]+0.2689264371002384*(fr[5]+fl[5]))+nuVtSqSum[0]*((-0.4640388251536715*fr[29])+0.4640388251536715*fl[29]+0.306186217847897*(fr[25]+fl[25]))+nuVtSqSum[3]*((-0.2314550249431378*fr[26])+0.2314550249431378*fl[26]-0.2766992952647331*fr[20]+0.2766992952647331*fl[20]+0.4279082480509108*(fr[14]+fl[14])+0.1825741858350553*(fr[13]+fl[13])-0.4640388251536715*fr[6]+0.4640388251536715*fl[6]+0.3061862178478971*(fr[3]+fl[3]))+nuVtSqSum[1]*((-0.4075699709865775*fr[20])+0.4075699709865775*fl[20]+0.2689264371002384*(fr[13]+fl[13])); 
  incr2[30] = nuVtSqSum[2]*((-1.897366596101028*fr[30])+1.897366596101028*fl[30]-3.735440486073895*fr[29]+3.735440486073895*fl[29]+2.464751508773247*(fr[25]+fl[25])+3.507803800100568*(fr[21]+fl[21])-3.803986395874726*fr[10]+3.803986395874726*fl[10]+2.509980079602226*(fr[5]+fl[5]))+nuVtSqSum[0]*((-2.121320343559642*fr[30])+2.121320343559642*fl[30]+3.921843874378478*(fr[21]+fl[21])-4.252986083330156*fr[10]+4.252986083330156*fl[10]+2.806243040080455*(fr[5]+fl[5]))+nuVtSqSum[1]*((-2.121320343559642*fr[26])+2.121320343559642*fl[26]-3.803986395874726*fr[20]+3.803986395874726*fl[20]+3.921843874378477*(fr[14]+fl[14])+2.509980079602227*(fr[13]+fl[13])-4.252986083330156*fr[6]+4.252986083330156*fl[6]+2.806243040080455*(fr[3]+fl[3]))+nuVtSqSum[3]*((-3.735440486073895*fr[20])+3.735440486073895*fl[20]+2.464751508773247*(fr[13]+fl[13])); 
  incr2[31] = nuVtSqSum[2]*((-0.4150489428970995*fr[31])+0.4150489428970995*fl[31]+0.2738612787525829*(fr[27]+fl[27]))+nuVtSqSum[0]*((-0.4640388251536715*fr[31])+0.4640388251536715*fl[31]+0.3061862178478971*(fr[27]+fl[27]))+nuVtSqSum[1]*((-0.4640388251536714*fr[28])+0.4640388251536714*fl[28]+0.3061862178478971*(fr[19]+fl[19])); 

  outr[0] += incr1[0]*rdv2R; 
  outr[1] += incr1[1]*rdv2R; 
  outr[2] += incr2[2]*rdvSq4R+incr1[2]*rdv2R; 
  outr[3] += incr1[3]*rdv2R; 
  outr[4] += incr2[4]*rdvSq4R+incr1[4]*rdv2R; 
  outr[5] += incr1[5]*rdv2R; 
  outr[6] += incr2[6]*rdvSq4R+incr1[6]*rdv2R; 
  outr[7] += incr1[7]*rdv2R; 
  outr[8] += incr2[8]*rdvSq4R+incr1[8]*rdv2R; 
  outr[9] += incr1[9]*rdv2R; 
  outr[10] += incr2[10]*rdvSq4R+incr1[10]*rdv2R; 
  outr[11] += incr2[11]*rdvSq4R+incr1[11]*rdv2R; 
  outr[12] += incr2[12]*rdvSq4R+incr1[12]*rdv2R; 
  outr[13] += incr1[13]*rdv2R; 
  outr[14] += incr2[14]*rdvSq4R+incr1[14]*rdv2R; 
  outr[15] += incr1[15]*rdv2R; 
  outr[16] += incr2[16]*rdvSq4R+incr1[16]*rdv2R; 
  outr[17] += incr1[17]*rdv2R; 
  outr[18] += incr2[18]*rdvSq4R+incr1[18]*rdv2R; 
  outr[19] += incr1[19]*rdv2R; 
  outr[20] += incr2[20]*rdvSq4R+incr1[20]*rdv2R; 
  outr[21] += incr2[21]*rdvSq4R+incr1[21]*rdv2R; 
  outr[22] += incr2[22]*rdvSq4R+incr1[22]*rdv2R; 
  outr[23] += incr2[23]*rdvSq4R+incr1[23]*rdv2R; 
  outr[24] += incr2[24]*rdvSq4R+incr1[24]*rdv2R; 
  outr[25] += incr1[25]*rdv2R; 
  outr[26] += incr2[26]*rdvSq4R+incr1[26]*rdv2R; 
  outr[27] += incr1[27]*rdv2R; 
  outr[28] += incr2[28]*rdvSq4R+incr1[28]*rdv2R; 
  outr[29] += incr2[29]*rdvSq4R+incr1[29]*rdv2R; 
  outr[30] += incr2[30]*rdvSq4R+incr1[30]*rdv2R; 
  outr[31] += incr2[31]*rdvSq4R+incr1[31]*rdv2R; 

  outl[0] += -1.0*incr1[0]*rdv2L; 
  outl[1] += -1.0*incr1[1]*rdv2L; 
  outl[2] += incr1[2]*rdv2L-1.0*incr2[2]*rdvSq4L; 
  outl[3] += -1.0*incr1[3]*rdv2L; 
  outl[4] += incr1[4]*rdv2L-1.0*incr2[4]*rdvSq4L; 
  outl[5] += -1.0*incr1[5]*rdv2L; 
  outl[6] += incr1[6]*rdv2L-1.0*incr2[6]*rdvSq4L; 
  outl[7] += -1.0*incr1[7]*rdv2L; 
  outl[8] += incr2[8]*rdvSq4L-1.0*incr1[8]*rdv2L; 
  outl[9] += -1.0*incr1[9]*rdv2L; 
  outl[10] += incr1[10]*rdv2L-1.0*incr2[10]*rdvSq4L; 
  outl[11] += incr1[11]*rdv2L-1.0*incr2[11]*rdvSq4L; 
  outl[12] += incr2[12]*rdvSq4L-1.0*incr1[12]*rdv2L; 
  outl[13] += -1.0*incr1[13]*rdv2L; 
  outl[14] += incr2[14]*rdvSq4L-1.0*incr1[14]*rdv2L; 
  outl[15] += -1.0*incr1[15]*rdv2L; 
  outl[16] += incr1[16]*rdv2L-1.0*incr2[16]*rdvSq4L; 
  outl[17] += -1.0*incr1[17]*rdv2L; 
  outl[18] += incr1[18]*rdv2L-1.0*incr2[18]*rdvSq4L; 
  outl[19] += -1.0*incr1[19]*rdv2L; 
  outl[20] += incr1[20]*rdv2L-1.0*incr2[20]*rdvSq4L; 
  outl[21] += incr2[21]*rdvSq4L-1.0*incr1[21]*rdv2L; 
  outl[22] += incr1[22]*rdv2L-1.0*incr2[22]*rdvSq4L; 
  outl[23] += incr1[23]*rdv2L-1.0*incr2[23]*rdvSq4L; 
  outl[24] += incr1[24]*rdv2L-1.0*incr2[24]*rdvSq4L; 
  outl[25] += -1.0*incr1[25]*rdv2L; 
  outl[26] += incr1[26]*rdv2L-1.0*incr2[26]*rdvSq4L; 
  outl[27] += -1.0*incr1[27]*rdv2L; 
  outl[28] += incr1[28]*rdv2L-1.0*incr2[28]*rdvSq4L; 
  outl[29] += incr1[29]*rdv2L-1.0*incr2[29]*rdvSq4L; 
  outl[30] += incr1[30]*rdv2L-1.0*incr2[30]*rdvSq4L; 
  outl[31] += incr1[31]*rdv2L-1.0*incr2[31]*rdvSq4L; 

  return std::abs((0.7905694150420947*sumNuUx[2])/nuSum-(0.7071067811865475*sumNuUx[0])/nuSum+wl[1]); 
} 
double VmLBOconstNuSurf1x2vSer_VY_P1(const double *wl, const double *wr, const double *dxvl, const double *dxvr, const double nuSum, const double vMuMidMax, const double *nuUSum, const double *nuVtSqSum, const double *fl, const double *fr, double *outl, double *outr) 
{ 
  // w[3]:          Cell-center coordinates. 
  // dxv[3]:        Cell spacing. 
  // nuSum:         collisionalities added (self and cross species collisionalities). 
  // vMuMidMax:     maximum midpoint value of v-u. 
  // nuUSum[4]:     sum of bulk velocities times their respective collisionalities. 
  // nuVtSqSum[2]:  sum of thermal speeds squared time their respective collisionalities. 
  // fl/fr:         Distribution function in left/right cells 
  // outl/outr:     Incremented distribution function in left/right cells 
  double rdv = 1.0/dxvl[2]; 
  double rdv2L = 2.0/dxvl[2]; 
  double rdv2R = 2.0/dxvr[2]; 
  double rdvSq4L = 4.0/(dxvl[2]*dxvl[2]); 
  double rdvSq4R = 4.0/(dxvr[2]*dxvr[2]); 

  const double *sumNuUy = &nuUSum[2]; 

  double favg[8]; 
  favg[0] = 1*fr[0]+fl[0]; 
  favg[1] = 1*fr[1]+fl[1]; 
  favg[2] = 1*fr[2]+fl[2]; 
  favg[3] = -1*fr[3]+fl[3]; 
  favg[4] = 1*fr[4]+fl[4]; 
  favg[5] = -1*fr[5]+fl[5]; 
  favg[6] = -1*fr[6]+fl[6]; 
  favg[7] = -1*fr[7]+fl[7]; 

  double fjump[8]; 
  fjump[0] = nuSum*vMuMidMax*(fl[0]-(1*fr[0])); 
  fjump[1] = nuSum*vMuMidMax*(fl[1]-(1*fr[1])); 
  fjump[2] = nuSum*vMuMidMax*(fl[2]-(1*fr[2])); 
  fjump[3] = nuSum*vMuMidMax*(fl[3]-(-1*fr[3])); 
  fjump[4] = nuSum*vMuMidMax*(fl[4]-(1*fr[4])); 
  fjump[5] = nuSum*vMuMidMax*(fl[5]-(-1*fr[5])); 
  fjump[6] = nuSum*vMuMidMax*(fl[6]-(-1*fr[6])); 
  fjump[7] = nuSum*vMuMidMax*(fl[7]-(-1*fr[7])); 

  double alphaDrag[2]; 
  alphaDrag[0] = 1.414213562373095*wl[2]*nuSum+0.7071067811865475*dxvl[2]*nuSum-1.0*sumNuUy[0]; 
  alphaDrag[1] = -1.0*sumNuUy[1]; 

  double Ghat[8]; 
  for(unsigned short int i=0; i<8; ++i){ 
    Ghat[i]=0.0; 
  }; 

  Ghat[0] = ((-1.530931089239486*nuVtSqSum[1]*fr[5])-1.530931089239486*nuVtSqSum[1]*fl[5]-1.530931089239486*nuVtSqSum[0]*fr[3]-1.530931089239486*nuVtSqSum[0]*fl[3]+1.590990257669731*fr[1]*nuVtSqSum[1]-1.590990257669731*fl[1]*nuVtSqSum[1]+1.590990257669731*fr[0]*nuVtSqSum[0]-1.590990257669731*fl[0]*nuVtSqSum[0])*rdv+alphaDrag[1]*(0.6123724356957944*favg[5]+0.3535533905932737*favg[1])-0.8660254037844386*fjump[3]+alphaDrag[0]*(0.6123724356957944*favg[3]+0.3535533905932737*favg[0])-0.5*fjump[0]; 
  Ghat[1] = ((-1.530931089239486*nuVtSqSum[0]*fr[5])-1.530931089239486*nuVtSqSum[0]*fl[5]-1.530931089239486*nuVtSqSum[1]*fr[3]-1.530931089239486*nuVtSqSum[1]*fl[3]+1.590990257669731*fr[0]*nuVtSqSum[1]-1.590990257669731*fl[0]*nuVtSqSum[1]+1.590990257669731*nuVtSqSum[0]*fr[1]-1.590990257669731*nuVtSqSum[0]*fl[1])*rdv-0.8660254037844386*fjump[5]+alphaDrag[0]*(0.6123724356957944*favg[5]+0.3535533905932737*favg[1])+alphaDrag[1]*(0.6123724356957944*favg[3]+0.3535533905932737*favg[0])-0.5*fjump[1]; 
  Ghat[2] = ((-1.530931089239486*nuVtSqSum[1]*fr[7])-1.530931089239486*nuVtSqSum[1]*fl[7]-1.530931089239486*nuVtSqSum[0]*fr[6]-1.530931089239486*nuVtSqSum[0]*fl[6]+1.590990257669731*nuVtSqSum[1]*fr[4]-1.590990257669731*nuVtSqSum[1]*fl[4]+1.590990257669731*nuVtSqSum[0]*fr[2]-1.590990257669731*nuVtSqSum[0]*fl[2])*rdv+alphaDrag[1]*(0.6123724356957944*favg[7]+0.3535533905932737*favg[4])-0.8660254037844386*fjump[6]+alphaDrag[0]*(0.6123724356957944*favg[6]+0.3535533905932737*favg[2])-0.5*fjump[2]; 
  Ghat[4] = ((-1.530931089239486*nuVtSqSum[0]*fr[7])-1.530931089239486*nuVtSqSum[0]*fl[7]-1.530931089239486*nuVtSqSum[1]*fr[6]-1.530931089239486*nuVtSqSum[1]*fl[6]+1.590990257669731*nuVtSqSum[0]*fr[4]-1.590990257669731*nuVtSqSum[0]*fl[4]+1.590990257669731*nuVtSqSum[1]*fr[2]-1.590990257669731*nuVtSqSum[1]*fl[2])*rdv-0.8660254037844386*fjump[7]+alphaDrag[0]*(0.6123724356957944*favg[7]+0.3535533905932737*favg[4])+alphaDrag[1]*(0.6123724356957944*favg[6]+0.3535533905932737*favg[2])-0.5*fjump[4]; 

  double incr1[8]; 
  incr1[0] = -0.5*Ghat[0]; 
  incr1[1] = -0.5*Ghat[1]; 
  incr1[2] = -0.5*Ghat[2]; 
  incr1[3] = 0.8660254037844386*Ghat[0]; 
  incr1[4] = -0.5*Ghat[4]; 
  incr1[5] = 0.8660254037844386*Ghat[1]; 
  incr1[6] = 0.8660254037844386*Ghat[2]; 
  incr1[7] = 0.8660254037844386*Ghat[4]; 

  double incr2[8]; 
  incr2[3] = nuVtSqSum[1]*((-0.3535533905932737*fr[5])+0.3535533905932737*fl[5]+0.3061862178478971*(fr[1]+fl[1]))+nuVtSqSum[0]*((-0.3535533905932737*fr[3])+0.3535533905932737*fl[3]+0.3061862178478971*(fr[0]+fl[0])); 
  incr2[5] = nuVtSqSum[0]*((-0.3535533905932737*fr[5])+0.3535533905932737*fl[5]+0.3061862178478971*(fr[1]+fl[1]))+nuVtSqSum[1]*((-0.3535533905932737*fr[3])+0.3535533905932737*fl[3]+0.3061862178478971*(fr[0]+fl[0])); 
  incr2[6] = nuVtSqSum[1]*((-0.3535533905932737*fr[7])+0.3535533905932737*fl[7]+0.3061862178478971*(fr[4]+fl[4]))+nuVtSqSum[0]*((-0.3535533905932737*fr[6])+0.3535533905932737*fl[6]+0.3061862178478971*(fr[2]+fl[2])); 
  incr2[7] = nuVtSqSum[0]*((-0.3535533905932737*fr[7])+0.3535533905932737*fl[7]+0.3061862178478971*(fr[4]+fl[4]))+nuVtSqSum[1]*((-0.3535533905932737*fr[6])+0.3535533905932737*fl[6]+0.3061862178478971*(fr[2]+fl[2])); 

  outr[0] += incr1[0]*rdv2R; 
  outr[1] += incr1[1]*rdv2R; 
  outr[2] += incr1[2]*rdv2R; 
  outr[3] += incr2[3]*rdvSq4R+incr1[3]*rdv2R; 
  outr[4] += incr1[4]*rdv2R; 
  outr[5] += incr2[5]*rdvSq4R+incr1[5]*rdv2R; 
  outr[6] += incr2[6]*rdvSq4R+incr1[6]*rdv2R; 
  outr[7] += incr2[7]*rdvSq4R+incr1[7]*rdv2R; 

  outl[0] += -1.0*incr1[0]*rdv2L; 
  outl[1] += -1.0*incr1[1]*rdv2L; 
  outl[2] += -1.0*incr1[2]*rdv2L; 
  outl[3] += incr1[3]*rdv2L-1.0*incr2[3]*rdvSq4L; 
  outl[4] += -1.0*incr1[4]*rdv2L; 
  outl[5] += incr1[5]*rdv2L-1.0*incr2[5]*rdvSq4L; 
  outl[6] += incr1[6]*rdv2L-1.0*incr2[6]*rdvSq4L; 
  outl[7] += incr1[7]*rdv2L-1.0*incr2[7]*rdvSq4L; 

  return std::abs(wl[2]-(0.7071067811865475*sumNuUy[0])/nuSum); 
} 
double VmLBOconstNuSurf1x2vSer_VY_P2(const double *wl, const double *wr, const double *dxvl, const double *dxvr, const double nuSum, const double vMuMidMax, const double *nuUSum, const double *nuVtSqSum, const double *fl, const double *fr, double *outl, double *outr) 
{ 
  // w[3]:          Cell-center coordinates. 
  // dxv[3]:        Cell spacing. 
  // nuSum:         collisionalities added (self and cross species collisionalities). 
  // vMuMidMax:     maximum midpoint value of v-u. 
  // nuUSum[6]:     sum of bulk velocities times their respective collisionalities. 
  // nuVtSqSum[3]:  sum of thermal speeds squared time their respective collisionalities. 
  // fl/fr:         Distribution function in left/right cells 
  // outl/outr:     Incremented distribution function in left/right cells 
  double rdv = 1.0/dxvl[2]; 
  double rdv2L = 2.0/dxvl[2]; 
  double rdv2R = 2.0/dxvr[2]; 
  double rdvSq4L = 4.0/(dxvl[2]*dxvl[2]); 
  double rdvSq4R = 4.0/(dxvr[2]*dxvr[2]); 

  const double *sumNuUy = &nuUSum[3]; 

  double favg[20]; 
  favg[0] = 1*fr[0]+fl[0]; 
  favg[1] = 1*fr[1]+fl[1]; 
  favg[2] = 1*fr[2]+fl[2]; 
  favg[3] = -1*fr[3]+fl[3]; 
  favg[4] = 1*fr[4]+fl[4]; 
  favg[5] = -1*fr[5]+fl[5]; 
  favg[6] = -1*fr[6]+fl[6]; 
  favg[7] = 1*fr[7]+fl[7]; 
  favg[8] = 1*fr[8]+fl[8]; 
  favg[9] = 1*fr[9]+fl[9]; 
  favg[10] = -1*fr[10]+fl[10]; 
  favg[11] = 1*fr[11]+fl[11]; 
  favg[12] = 1*fr[12]+fl[12]; 
  favg[13] = -1*fr[13]+fl[13]; 
  favg[14] = -1*fr[14]+fl[14]; 
  favg[15] = 1*fr[15]+fl[15]; 
  favg[16] = 1*fr[16]+fl[16]; 
  favg[17] = -1*fr[17]+fl[17]; 
  favg[18] = -1*fr[18]+fl[18]; 
  favg[19] = 1*fr[19]+fl[19]; 

  double fjump[20]; 
  fjump[0] = nuSum*vMuMidMax*(fl[0]-(1*fr[0])); 
  fjump[1] = nuSum*vMuMidMax*(fl[1]-(1*fr[1])); 
  fjump[2] = nuSum*vMuMidMax*(fl[2]-(1*fr[2])); 
  fjump[3] = nuSum*vMuMidMax*(fl[3]-(-1*fr[3])); 
  fjump[4] = nuSum*vMuMidMax*(fl[4]-(1*fr[4])); 
  fjump[5] = nuSum*vMuMidMax*(fl[5]-(-1*fr[5])); 
  fjump[6] = nuSum*vMuMidMax*(fl[6]-(-1*fr[6])); 
  fjump[7] = nuSum*vMuMidMax*(fl[7]-(1*fr[7])); 
  fjump[8] = nuSum*vMuMidMax*(fl[8]-(1*fr[8])); 
  fjump[9] = nuSum*vMuMidMax*(fl[9]-(1*fr[9])); 
  fjump[10] = nuSum*vMuMidMax*(fl[10]-(-1*fr[10])); 
  fjump[11] = nuSum*vMuMidMax*(fl[11]-(1*fr[11])); 
  fjump[12] = nuSum*vMuMidMax*(fl[12]-(1*fr[12])); 
  fjump[13] = nuSum*vMuMidMax*(fl[13]-(-1*fr[13])); 
  fjump[14] = nuSum*vMuMidMax*(fl[14]-(-1*fr[14])); 
  fjump[15] = nuSum*vMuMidMax*(fl[15]-(1*fr[15])); 
  fjump[16] = nuSum*vMuMidMax*(fl[16]-(1*fr[16])); 
  fjump[17] = nuSum*vMuMidMax*(fl[17]-(-1*fr[17])); 
  fjump[18] = nuSum*vMuMidMax*(fl[18]-(-1*fr[18])); 
  fjump[19] = nuSum*vMuMidMax*(fl[19]-(1*fr[19])); 

  double alphaDrag[3]; 
  alphaDrag[0] = 1.414213562373095*wl[2]*nuSum+0.7071067811865475*dxvl[2]*nuSum-1.0*sumNuUy[0]; 
  alphaDrag[1] = -1.0*sumNuUy[1]; 
  alphaDrag[2] = -1.0*sumNuUy[2]; 

  double Ghat[20]; 
  for(unsigned short int i=0; i<20; ++i){ 
    Ghat[i]=0.0; 
  }; 

  Ghat[0] = (1.897366596101028*nuVtSqSum[1]*fr[15]-1.897366596101028*nuVtSqSum[1]*fl[15]-3.368048396326869*nuVtSqSum[2]*fr[13]-3.368048396326869*nuVtSqSum[2]*fl[13]+1.897366596101028*nuVtSqSum[0]*fr[9]-1.897366596101028*nuVtSqSum[0]*fl[9]+2.651650429449552*nuVtSqSum[2]*fr[7]-2.651650429449552*nuVtSqSum[2]*fl[7]-3.368048396326869*nuVtSqSum[1]*fr[5]-3.368048396326869*nuVtSqSum[1]*fl[5]-3.368048396326869*nuVtSqSum[0]*fr[3]-3.368048396326869*nuVtSqSum[0]*fl[3]+2.651650429449552*fr[1]*nuVtSqSum[1]-2.651650429449552*fl[1]*nuVtSqSum[1]+2.651650429449552*fr[0]*nuVtSqSum[0]-2.651650429449552*fl[0]*nuVtSqSum[0])*rdv+alphaDrag[1]*(0.7905694150420948*favg[15]+0.6123724356957944*favg[5]+0.3535533905932737*favg[1])+alphaDrag[2]*(0.6123724356957944*favg[13]+0.3535533905932737*favg[7])-1.118033988749895*fjump[9]+alphaDrag[0]*(0.7905694150420947*favg[9]+0.6123724356957944*favg[3]+0.3535533905932737*favg[0])-0.8660254037844386*fjump[3]-0.5*fjump[0]; 
  Ghat[1] = (1.697056274847714*nuVtSqSum[2]*fr[15]+1.897366596101028*nuVtSqSum[0]*fr[15]-1.697056274847714*nuVtSqSum[2]*fl[15]-1.897366596101028*nuVtSqSum[0]*fl[15]-3.012474066278414*nuVtSqSum[1]*fr[13]-3.012474066278414*nuVtSqSum[1]*fl[13]+1.897366596101028*nuVtSqSum[1]*fr[9]-1.897366596101028*nuVtSqSum[1]*fl[9]+2.371708245126284*nuVtSqSum[1]*fr[7]-2.371708245126284*nuVtSqSum[1]*fl[7]-3.012474066278413*nuVtSqSum[2]*fr[5]-3.368048396326869*nuVtSqSum[0]*fr[5]-3.012474066278413*nuVtSqSum[2]*fl[5]-3.368048396326869*nuVtSqSum[0]*fl[5]-3.368048396326869*nuVtSqSum[1]*fr[3]-3.368048396326869*nuVtSqSum[1]*fl[3]+2.371708245126284*fr[1]*nuVtSqSum[2]-2.371708245126284*fl[1]*nuVtSqSum[2]+2.651650429449552*fr[0]*nuVtSqSum[1]-2.651650429449552*fl[0]*nuVtSqSum[1]+2.651650429449552*nuVtSqSum[0]*fr[1]-2.651650429449552*nuVtSqSum[0]*fl[1])*rdv-1.118033988749895*fjump[15]+alphaDrag[0]*(0.7905694150420948*favg[15]+0.6123724356957944*favg[5]+0.3535533905932737*favg[1])+alphaDrag[2]*(0.7071067811865475*favg[15]+0.5477225575051661*favg[5]+0.3162277660168379*favg[1])+alphaDrag[1]*(0.5477225575051661*favg[13]+0.7905694150420947*favg[9]+0.3162277660168379*favg[7]+0.6123724356957944*favg[3]+0.3535533905932737*favg[0])-0.8660254037844386*fjump[5]-0.5*fjump[1]; 
  Ghat[2] = (1.897366596101028*nuVtSqSum[1]*fr[19]-1.897366596101028*nuVtSqSum[1]*fl[19]-3.368048396326869*nuVtSqSum[2]*fr[17]-3.368048396326869*nuVtSqSum[2]*fl[17]+1.897366596101028*nuVtSqSum[0]*fr[16]-1.897366596101028*nuVtSqSum[0]*fl[16]+2.651650429449552*nuVtSqSum[2]*fr[11]-2.651650429449552*nuVtSqSum[2]*fl[11]-3.368048396326869*nuVtSqSum[1]*fr[10]-3.368048396326869*nuVtSqSum[1]*fl[10]-3.368048396326869*nuVtSqSum[0]*fr[6]-3.368048396326869*nuVtSqSum[0]*fl[6]+2.651650429449552*nuVtSqSum[1]*fr[4]-2.651650429449552*nuVtSqSum[1]*fl[4]+2.651650429449552*nuVtSqSum[0]*fr[2]-2.651650429449552*nuVtSqSum[0]*fl[2])*rdv+alphaDrag[1]*(0.7905694150420947*favg[19]+0.6123724356957944*favg[10]+0.3535533905932737*favg[4])+alphaDrag[2]*(0.6123724356957944*favg[17]+0.3535533905932737*favg[11])-1.118033988749895*fjump[16]+alphaDrag[0]*(0.7905694150420948*favg[16]+0.6123724356957944*favg[6]+0.3535533905932737*favg[2])-0.8660254037844386*fjump[6]-0.5*fjump[2]; 
  Ghat[4] = (1.697056274847714*nuVtSqSum[2]*fr[19]+1.897366596101028*nuVtSqSum[0]*fr[19]-1.697056274847714*nuVtSqSum[2]*fl[19]-1.897366596101028*nuVtSqSum[0]*fl[19]-3.012474066278413*nuVtSqSum[1]*fr[17]-3.012474066278413*nuVtSqSum[1]*fl[17]+1.897366596101028*nuVtSqSum[1]*fr[16]-1.897366596101028*nuVtSqSum[1]*fl[16]+2.371708245126284*nuVtSqSum[1]*fr[11]-2.371708245126284*nuVtSqSum[1]*fl[11]-3.012474066278413*nuVtSqSum[2]*fr[10]-3.368048396326869*nuVtSqSum[0]*fr[10]-3.012474066278413*nuVtSqSum[2]*fl[10]-3.368048396326869*nuVtSqSum[0]*fl[10]-3.368048396326869*nuVtSqSum[1]*fr[6]-3.368048396326869*nuVtSqSum[1]*fl[6]+2.371708245126284*nuVtSqSum[2]*fr[4]+2.651650429449552*nuVtSqSum[0]*fr[4]-2.371708245126284*nuVtSqSum[2]*fl[4]-2.651650429449552*nuVtSqSum[0]*fl[4]+2.651650429449552*nuVtSqSum[1]*fr[2]-2.651650429449552*nuVtSqSum[1]*fl[2])*rdv-1.118033988749895*fjump[19]+alphaDrag[0]*(0.7905694150420947*favg[19]+0.6123724356957944*favg[10]+0.3535533905932737*favg[4])+alphaDrag[2]*(0.7071067811865475*favg[19]+0.5477225575051661*favg[10]+0.3162277660168379*favg[4])+alphaDrag[1]*(0.5477225575051661*favg[17]+0.7905694150420948*favg[16]+0.3162277660168379*favg[11]+0.6123724356957944*favg[6]+0.3535533905932737*favg[2])-0.8660254037844386*fjump[10]-0.5*fjump[4]; 
  Ghat[7] = (1.697056274847714*nuVtSqSum[1]*fr[15]-1.697056274847714*nuVtSqSum[1]*fl[15]-2.151767190198866*nuVtSqSum[2]*fr[13]-3.368048396326869*nuVtSqSum[0]*fr[13]-2.151767190198866*nuVtSqSum[2]*fl[13]-3.368048396326869*nuVtSqSum[0]*fl[13]+1.897366596101028*nuVtSqSum[2]*fr[9]-1.897366596101028*nuVtSqSum[2]*fl[9]+1.694077317947346*nuVtSqSum[2]*fr[7]+2.651650429449552*nuVtSqSum[0]*fr[7]-1.694077317947346*nuVtSqSum[2]*fl[7]-2.651650429449552*nuVtSqSum[0]*fl[7]-3.012474066278413*nuVtSqSum[1]*fr[5]-3.012474066278413*nuVtSqSum[1]*fl[5]-3.368048396326869*nuVtSqSum[2]*fr[3]-3.368048396326869*nuVtSqSum[2]*fl[3]+2.651650429449552*fr[0]*nuVtSqSum[2]-2.651650429449552*fl[0]*nuVtSqSum[2]+2.371708245126284*fr[1]*nuVtSqSum[1]-2.371708245126284*fl[1]*nuVtSqSum[1])*rdv+alphaDrag[1]*(0.7071067811865475*favg[15]+0.5477225575051661*favg[5]+0.3162277660168379*favg[1])-0.8660254037844387*fjump[13]+alphaDrag[0]*(0.6123724356957944*favg[13]+0.3535533905932737*favg[7])+alphaDrag[2]*(0.3912303982179757*favg[13]+0.7905694150420947*favg[9]+0.2258769757263128*favg[7]+0.6123724356957944*favg[3]+0.3535533905932737*favg[0])-0.5*fjump[7]; 
  Ghat[8] = ((-3.368048396326869*nuVtSqSum[1]*fr[18])-3.368048396326869*nuVtSqSum[1]*fl[18]-3.368048396326869*nuVtSqSum[0]*fr[14]-3.368048396326869*nuVtSqSum[0]*fl[14]+2.651650429449552*nuVtSqSum[1]*fr[12]-2.651650429449552*nuVtSqSum[1]*fl[12]+2.651650429449552*nuVtSqSum[0]*fr[8]-2.651650429449552*nuVtSqSum[0]*fl[8])*rdv+alphaDrag[1]*(0.6123724356957944*favg[18]+0.3535533905932737*favg[12])-0.8660254037844387*fjump[14]+alphaDrag[0]*(0.6123724356957944*favg[14]+0.3535533905932737*favg[8])-0.5*fjump[8]; 
  Ghat[11] = (1.697056274847714*nuVtSqSum[1]*fr[19]-1.697056274847714*nuVtSqSum[1]*fl[19]-2.151767190198866*nuVtSqSum[2]*fr[17]-3.368048396326869*nuVtSqSum[0]*fr[17]-2.151767190198866*nuVtSqSum[2]*fl[17]-3.368048396326869*nuVtSqSum[0]*fl[17]+1.897366596101028*nuVtSqSum[2]*fr[16]-1.897366596101028*nuVtSqSum[2]*fl[16]+1.694077317947346*nuVtSqSum[2]*fr[11]+2.651650429449552*nuVtSqSum[0]*fr[11]-1.694077317947346*nuVtSqSum[2]*fl[11]-2.651650429449552*nuVtSqSum[0]*fl[11]-3.012474066278414*nuVtSqSum[1]*fr[10]-3.012474066278414*nuVtSqSum[1]*fl[10]-3.368048396326869*nuVtSqSum[2]*fr[6]-3.368048396326869*nuVtSqSum[2]*fl[6]+2.371708245126284*nuVtSqSum[1]*fr[4]-2.371708245126284*nuVtSqSum[1]*fl[4]+2.651650429449552*fr[2]*nuVtSqSum[2]-2.651650429449552*fl[2]*nuVtSqSum[2])*rdv+alphaDrag[1]*(0.7071067811865475*favg[19]+0.5477225575051661*favg[10]+0.3162277660168379*favg[4])-0.8660254037844387*fjump[17]+alphaDrag[0]*(0.6123724356957944*favg[17]+0.3535533905932737*favg[11])+alphaDrag[2]*(0.3912303982179757*favg[17]+0.7905694150420947*favg[16]+0.2258769757263128*favg[11]+0.6123724356957944*favg[6]+0.3535533905932737*favg[2])-0.5*fjump[11]; 
  Ghat[12] = ((-3.012474066278414*nuVtSqSum[2]*fr[18])-3.368048396326869*nuVtSqSum[0]*fr[18]-3.012474066278414*nuVtSqSum[2]*fl[18]-3.368048396326869*nuVtSqSum[0]*fl[18]-3.368048396326869*nuVtSqSum[1]*fr[14]-3.368048396326869*nuVtSqSum[1]*fl[14]+2.371708245126284*nuVtSqSum[2]*fr[12]+2.651650429449552*nuVtSqSum[0]*fr[12]-2.371708245126284*nuVtSqSum[2]*fl[12]-2.651650429449552*nuVtSqSum[0]*fl[12]+2.651650429449552*nuVtSqSum[1]*fr[8]-2.651650429449552*nuVtSqSum[1]*fl[8])*rdv-0.8660254037844387*fjump[18]+alphaDrag[0]*(0.6123724356957944*favg[18]+0.3535533905932737*favg[12])+alphaDrag[2]*(0.5477225575051661*favg[18]+0.3162277660168379*favg[12])+alphaDrag[1]*(0.6123724356957944*favg[14]+0.3535533905932737*favg[8])-0.5*fjump[12]; 

  double incr1[20]; 
  incr1[0] = -0.5*Ghat[0]; 
  incr1[1] = -0.5*Ghat[1]; 
  incr1[2] = -0.5*Ghat[2]; 
  incr1[3] = 0.8660254037844386*Ghat[0]; 
  incr1[4] = -0.5*Ghat[4]; 
  incr1[5] = 0.8660254037844386*Ghat[1]; 
  incr1[6] = 0.8660254037844386*Ghat[2]; 
  incr1[7] = -0.5*Ghat[7]; 
  incr1[8] = -0.5*Ghat[8]; 
  incr1[9] = -1.118033988749895*Ghat[0]; 
  incr1[10] = 0.8660254037844386*Ghat[4]; 
  incr1[11] = -0.5*Ghat[11]; 
  incr1[12] = -0.5*Ghat[12]; 
  incr1[13] = 0.8660254037844387*Ghat[7]; 
  incr1[14] = 0.8660254037844387*Ghat[8]; 
  incr1[15] = -1.118033988749895*Ghat[1]; 
  incr1[16] = -1.118033988749895*Ghat[2]; 
  incr1[17] = 0.8660254037844387*Ghat[11]; 
  incr1[18] = 0.8660254037844387*Ghat[12]; 
  incr1[19] = -1.118033988749895*Ghat[4]; 

  double incr2[20]; 
  incr2[3] = nuVtSqSum[1]*(0.2995357736356374*(fr[15]+fl[15])-0.430893194785552*fr[5]+0.430893194785552*fl[5]+0.3061862178478971*(fr[1]+fl[1]))+nuVtSqSum[2]*((-0.430893194785552*fr[13])+0.430893194785552*fl[13]+0.3061862178478971*(fr[7]+fl[7]))+nuVtSqSum[0]*(0.2995357736356374*(fr[9]+fl[9])-0.430893194785552*fr[3]+0.430893194785552*fl[3]+0.3061862178478971*(fr[0]+fl[0])); 
  incr2[5] = nuVtSqSum[0]*(0.2995357736356374*(fr[15]+fl[15])-0.430893194785552*fr[5]+0.430893194785552*fl[5]+0.3061862178478971*(fr[1]+fl[1]))+nuVtSqSum[2]*(0.2679129406169099*(fr[15]+fl[15])-0.3854025898330209*fr[5]+0.3854025898330209*fl[5]+0.273861278752583*(fr[1]+fl[1]))+nuVtSqSum[1]*((-0.3854025898330209*fr[13])+0.3854025898330209*fl[13]+0.2995357736356374*(fr[9]+fl[9])+0.273861278752583*(fr[7]+fl[7])-0.430893194785552*fr[3]+0.430893194785552*fl[3]+0.3061862178478971*(fr[0]+fl[0])); 
  incr2[6] = nuVtSqSum[1]*(0.2995357736356374*(fr[19]+fl[19])-0.430893194785552*fr[10]+0.430893194785552*fl[10]+0.3061862178478971*(fr[4]+fl[4]))+nuVtSqSum[2]*((-0.430893194785552*fr[17])+0.430893194785552*fl[17]+0.3061862178478971*(fr[11]+fl[11]))+nuVtSqSum[0]*(0.2995357736356374*(fr[16]+fl[16])-0.430893194785552*fr[6]+0.430893194785552*fl[6]+0.3061862178478971*(fr[2]+fl[2])); 
  incr2[9] = nuVtSqSum[1]*((-1.160097062884178*(fr[15]+fl[15]))+1.668842167398551*fr[5]-1.668842167398551*fl[5]-1.185854122563142*(fr[1]+fl[1]))+nuVtSqSum[2]*(1.668842167398552*fr[13]-1.668842167398552*fl[13]-1.185854122563142*(fr[7]+fl[7]))+nuVtSqSum[0]*((-1.160097062884178*(fr[9]+fl[9]))+1.668842167398551*fr[3]-1.668842167398551*fl[3]-1.185854122563142*(fr[0]+fl[0])); 
  incr2[10] = nuVtSqSum[0]*(0.2995357736356374*(fr[19]+fl[19])-0.430893194785552*fr[10]+0.430893194785552*fl[10]+0.3061862178478971*(fr[4]+fl[4]))+nuVtSqSum[2]*(0.2679129406169099*(fr[19]+fl[19])-0.3854025898330209*fr[10]+0.3854025898330209*fl[10]+0.273861278752583*(fr[4]+fl[4]))+nuVtSqSum[1]*((-0.3854025898330209*fr[17])+0.3854025898330209*fl[17]+0.2995357736356374*(fr[16]+fl[16])+0.273861278752583*(fr[11]+fl[11])-0.430893194785552*fr[6]+0.430893194785552*fl[6]+0.3061862178478971*(fr[2]+fl[2])); 
  incr2[13] = nuVtSqSum[1]*(0.2679129406169099*(fr[15]+fl[15])-0.3854025898330209*fr[5]+0.3854025898330209*fl[5]+0.273861278752583*(fr[1]+fl[1]))+nuVtSqSum[2]*((-0.2752875641664436*fr[13])+0.2752875641664436*fl[13]+0.2995357736356374*(fr[9]+fl[9])+0.1956151991089878*(fr[7]+fl[7])-0.430893194785552*fr[3]+0.430893194785552*fl[3]+0.3061862178478971*(fr[0]+fl[0]))+nuVtSqSum[0]*((-0.430893194785552*fr[13])+0.430893194785552*fl[13]+0.3061862178478971*(fr[7]+fl[7])); 
  incr2[14] = nuVtSqSum[1]*((-0.430893194785552*fr[18])+0.430893194785552*fl[18]+0.3061862178478971*(fr[12]+fl[12]))+nuVtSqSum[0]*((-0.430893194785552*fr[14])+0.430893194785552*fl[14]+0.3061862178478971*(fr[8]+fl[8])); 
  incr2[15] = nuVtSqSum[2]*((-1.037622357242749*(fr[15]+fl[15]))+1.492657812008498*fr[5]-1.492657812008498*fl[5]-1.060660171779821*(fr[1]+fl[1]))+nuVtSqSum[0]*((-1.160097062884178*(fr[15]+fl[15]))+1.668842167398552*fr[5]-1.668842167398552*fl[5]-1.185854122563142*(fr[1]+fl[1]))+nuVtSqSum[1]*(1.492657812008498*fr[13]-1.492657812008498*fl[13]-1.160097062884178*(fr[9]+fl[9])-1.060660171779821*(fr[7]+fl[7])+1.668842167398552*fr[3]-1.668842167398552*fl[3]-1.185854122563142*(fr[0]+fl[0])); 
  incr2[16] = nuVtSqSum[1]*((-1.160097062884178*(fr[19]+fl[19]))+1.668842167398552*fr[10]-1.668842167398552*fl[10]-1.185854122563142*(fr[4]+fl[4]))+nuVtSqSum[2]*(1.668842167398552*fr[17]-1.668842167398552*fl[17]-1.185854122563142*(fr[11]+fl[11]))+nuVtSqSum[0]*((-1.160097062884178*(fr[16]+fl[16]))+1.668842167398552*fr[6]-1.668842167398552*fl[6]-1.185854122563142*(fr[2]+fl[2])); 
  incr2[17] = nuVtSqSum[1]*(0.2679129406169099*(fr[19]+fl[19])-0.3854025898330209*fr[10]+0.3854025898330209*fl[10]+0.273861278752583*(fr[4]+fl[4]))+nuVtSqSum[2]*((-0.2752875641664436*fr[17])+0.2752875641664436*fl[17]+0.2995357736356374*(fr[16]+fl[16])+0.1956151991089878*(fr[11]+fl[11])-0.430893194785552*fr[6]+0.430893194785552*fl[6]+0.3061862178478971*(fr[2]+fl[2]))+nuVtSqSum[0]*((-0.430893194785552*fr[17])+0.430893194785552*fl[17]+0.3061862178478971*(fr[11]+fl[11])); 
  incr2[18] = nuVtSqSum[2]*((-0.3854025898330209*fr[18])+0.3854025898330209*fl[18]+0.273861278752583*(fr[12]+fl[12]))+nuVtSqSum[0]*((-0.430893194785552*fr[18])+0.430893194785552*fl[18]+0.3061862178478971*(fr[12]+fl[12]))+nuVtSqSum[1]*((-0.430893194785552*fr[14])+0.430893194785552*fl[14]+0.3061862178478971*(fr[8]+fl[8])); 
  incr2[19] = nuVtSqSum[2]*((-1.037622357242749*(fr[19]+fl[19]))+1.492657812008498*fr[10]-1.492657812008498*fl[10]-1.060660171779821*(fr[4]+fl[4]))+nuVtSqSum[0]*((-1.160097062884178*(fr[19]+fl[19]))+1.668842167398551*fr[10]-1.668842167398551*fl[10]-1.185854122563142*(fr[4]+fl[4]))+nuVtSqSum[1]*(1.492657812008498*fr[17]-1.492657812008498*fl[17]-1.160097062884178*(fr[16]+fl[16])-1.060660171779821*(fr[11]+fl[11])+1.668842167398551*fr[6]-1.668842167398551*fl[6]-1.185854122563142*(fr[2]+fl[2])); 

  outr[0] += incr1[0]*rdv2R; 
  outr[1] += incr1[1]*rdv2R; 
  outr[2] += incr1[2]*rdv2R; 
  outr[3] += incr2[3]*rdvSq4R+incr1[3]*rdv2R; 
  outr[4] += incr1[4]*rdv2R; 
  outr[5] += incr2[5]*rdvSq4R+incr1[5]*rdv2R; 
  outr[6] += incr2[6]*rdvSq4R+incr1[6]*rdv2R; 
  outr[7] += incr1[7]*rdv2R; 
  outr[8] += incr1[8]*rdv2R; 
  outr[9] += incr2[9]*rdvSq4R+incr1[9]*rdv2R; 
  outr[10] += incr2[10]*rdvSq4R+incr1[10]*rdv2R; 
  outr[11] += incr1[11]*rdv2R; 
  outr[12] += incr1[12]*rdv2R; 
  outr[13] += incr2[13]*rdvSq4R+incr1[13]*rdv2R; 
  outr[14] += incr2[14]*rdvSq4R+incr1[14]*rdv2R; 
  outr[15] += incr2[15]*rdvSq4R+incr1[15]*rdv2R; 
  outr[16] += incr2[16]*rdvSq4R+incr1[16]*rdv2R; 
  outr[17] += incr2[17]*rdvSq4R+incr1[17]*rdv2R; 
  outr[18] += incr2[18]*rdvSq4R+incr1[18]*rdv2R; 
  outr[19] += incr2[19]*rdvSq4R+incr1[19]*rdv2R; 

  outl[0] += -1.0*incr1[0]*rdv2L; 
  outl[1] += -1.0*incr1[1]*rdv2L; 
  outl[2] += -1.0*incr1[2]*rdv2L; 
  outl[3] += incr1[3]*rdv2L-1.0*incr2[3]*rdvSq4L; 
  outl[4] += -1.0*incr1[4]*rdv2L; 
  outl[5] += incr1[5]*rdv2L-1.0*incr2[5]*rdvSq4L; 
  outl[6] += incr1[6]*rdv2L-1.0*incr2[6]*rdvSq4L; 
  outl[7] += -1.0*incr1[7]*rdv2L; 
  outl[8] += -1.0*incr1[8]*rdv2L; 
  outl[9] += incr2[9]*rdvSq4L-1.0*incr1[9]*rdv2L; 
  outl[10] += incr1[10]*rdv2L-1.0*incr2[10]*rdvSq4L; 
  outl[11] += -1.0*incr1[11]*rdv2L; 
  outl[12] += -1.0*incr1[12]*rdv2L; 
  outl[13] += incr1[13]*rdv2L-1.0*incr2[13]*rdvSq4L; 
  outl[14] += incr1[14]*rdv2L-1.0*incr2[14]*rdvSq4L; 
  outl[15] += incr2[15]*rdvSq4L-1.0*incr1[15]*rdv2L; 
  outl[16] += incr2[16]*rdvSq4L-1.0*incr1[16]*rdv2L; 
  outl[17] += incr1[17]*rdv2L-1.0*incr2[17]*rdvSq4L; 
  outl[18] += incr1[18]*rdv2L-1.0*incr2[18]*rdvSq4L; 
  outl[19] += incr2[19]*rdvSq4L-1.0*incr1[19]*rdv2L; 

  return std::abs((0.7905694150420947*sumNuUy[2])/nuSum-(0.7071067811865475*sumNuUy[0])/nuSum+wl[2]); 
} 
double VmLBOconstNuSurf1x2vSer_VY_P3(const double *wl, const double *wr, const double *dxvl, const double *dxvr, const double nuSum, const double vMuMidMax, const double *nuUSum, const double *nuVtSqSum, const double *fl, const double *fr, double *outl, double *outr) 
{ 
  // w[3]:          Cell-center coordinates. 
  // dxv[3]:        Cell spacing. 
  // nuSum:         collisionalities added (self and cross species collisionalities). 
  // vMuMidMax:     maximum midpoint value of v-u. 
  // nuUSum[8]:     sum of bulk velocities times their respective collisionalities. 
  // nuVtSqSum[4]:  sum of thermal speeds squared time their respective collisionalities. 
  // fl/fr:         Distribution function in left/right cells 
  // outl/outr:     Incremented distribution function in left/right cells 
  double rdv = 1.0/dxvl[2]; 
  double rdv2L = 2.0/dxvl[2]; 
  double rdv2R = 2.0/dxvr[2]; 
  double rdvSq4L = 4.0/(dxvl[2]*dxvl[2]); 
  double rdvSq4R = 4.0/(dxvr[2]*dxvr[2]); 

  const double *sumNuUy = &nuUSum[4]; 

  double favg[32]; 
  favg[0] = 1*fr[0]+fl[0]; 
  favg[1] = 1*fr[1]+fl[1]; 
  favg[2] = 1*fr[2]+fl[2]; 
  favg[3] = -1*fr[3]+fl[3]; 
  favg[4] = 1*fr[4]+fl[4]; 
  favg[5] = -1*fr[5]+fl[5]; 
  favg[6] = -1*fr[6]+fl[6]; 
  favg[7] = 1*fr[7]+fl[7]; 
  favg[8] = 1*fr[8]+fl[8]; 
  favg[9] = 1*fr[9]+fl[9]; 
  favg[10] = -1*fr[10]+fl[10]; 
  favg[11] = 1*fr[11]+fl[11]; 
  favg[12] = 1*fr[12]+fl[12]; 
  favg[13] = -1*fr[13]+fl[13]; 
  favg[14] = -1*fr[14]+fl[14]; 
  favg[15] = 1*fr[15]+fl[15]; 
  favg[16] = 1*fr[16]+fl[16]; 
  favg[17] = 1*fr[17]+fl[17]; 
  favg[18] = 1*fr[18]+fl[18]; 
  favg[19] = -1*fr[19]+fl[19]; 
  favg[20] = -1*fr[20]+fl[20]; 
  favg[21] = -1*fr[21]+fl[21]; 
  favg[22] = 1*fr[22]+fl[22]; 
  favg[23] = 1*fr[23]+fl[23]; 
  favg[24] = 1*fr[24]+fl[24]; 
  favg[25] = -1*fr[25]+fl[25]; 
  favg[26] = -1*fr[26]+fl[26]; 
  favg[27] = -1*fr[27]+fl[27]; 
  favg[28] = -1*fr[28]+fl[28]; 
  favg[29] = -1*fr[29]+fl[29]; 
  favg[30] = -1*fr[30]+fl[30]; 
  favg[31] = -1*fr[31]+fl[31]; 

  double fjump[32]; 
  fjump[0] = nuSum*vMuMidMax*(fl[0]-(1*fr[0])); 
  fjump[1] = nuSum*vMuMidMax*(fl[1]-(1*fr[1])); 
  fjump[2] = nuSum*vMuMidMax*(fl[2]-(1*fr[2])); 
  fjump[3] = nuSum*vMuMidMax*(fl[3]-(-1*fr[3])); 
  fjump[4] = nuSum*vMuMidMax*(fl[4]-(1*fr[4])); 
  fjump[5] = nuSum*vMuMidMax*(fl[5]-(-1*fr[5])); 
  fjump[6] = nuSum*vMuMidMax*(fl[6]-(-1*fr[6])); 
  fjump[7] = nuSum*vMuMidMax*(fl[7]-(1*fr[7])); 
  fjump[8] = nuSum*vMuMidMax*(fl[8]-(1*fr[8])); 
  fjump[9] = nuSum*vMuMidMax*(fl[9]-(1*fr[9])); 
  fjump[10] = nuSum*vMuMidMax*(fl[10]-(-1*fr[10])); 
  fjump[11] = nuSum*vMuMidMax*(fl[11]-(1*fr[11])); 
  fjump[12] = nuSum*vMuMidMax*(fl[12]-(1*fr[12])); 
  fjump[13] = nuSum*vMuMidMax*(fl[13]-(-1*fr[13])); 
  fjump[14] = nuSum*vMuMidMax*(fl[14]-(-1*fr[14])); 
  fjump[15] = nuSum*vMuMidMax*(fl[15]-(1*fr[15])); 
  fjump[16] = nuSum*vMuMidMax*(fl[16]-(1*fr[16])); 
  fjump[17] = nuSum*vMuMidMax*(fl[17]-(1*fr[17])); 
  fjump[18] = nuSum*vMuMidMax*(fl[18]-(1*fr[18])); 
  fjump[19] = nuSum*vMuMidMax*(fl[19]-(-1*fr[19])); 
  fjump[20] = nuSum*vMuMidMax*(fl[20]-(-1*fr[20])); 
  fjump[21] = nuSum*vMuMidMax*(fl[21]-(-1*fr[21])); 
  fjump[22] = nuSum*vMuMidMax*(fl[22]-(1*fr[22])); 
  fjump[23] = nuSum*vMuMidMax*(fl[23]-(1*fr[23])); 
  fjump[24] = nuSum*vMuMidMax*(fl[24]-(1*fr[24])); 
  fjump[25] = nuSum*vMuMidMax*(fl[25]-(-1*fr[25])); 
  fjump[26] = nuSum*vMuMidMax*(fl[26]-(-1*fr[26])); 
  fjump[27] = nuSum*vMuMidMax*(fl[27]-(-1*fr[27])); 
  fjump[28] = nuSum*vMuMidMax*(fl[28]-(-1*fr[28])); 
  fjump[29] = nuSum*vMuMidMax*(fl[29]-(-1*fr[29])); 
  fjump[30] = nuSum*vMuMidMax*(fl[30]-(-1*fr[30])); 
  fjump[31] = nuSum*vMuMidMax*(fl[31]-(-1*fr[31])); 

  double alphaDrag[4]; 
  alphaDrag[0] = 1.414213562373095*wl[2]*nuSum+0.7071067811865475*dxvl[2]*nuSum-1.0*sumNuUy[0]; 
  alphaDrag[1] = -1.0*sumNuUy[1]; 
  alphaDrag[2] = -1.0*sumNuUy[2]; 
  alphaDrag[3] = -1.0*sumNuUy[3]; 

  double Ghat[32]; 
  for(unsigned short int i=0; i<32; ++i){ 
    Ghat[i]=0.0; 
  }; 

  Ghat[0] = ((-1.929292090055312*nuVtSqSum[1]*fr[27])-1.929292090055312*nuVtSqSum[1]*fl[27]-5.473078644031158*nuVtSqSum[3]*fr[25]-5.473078644031158*nuVtSqSum[3]*fl[25]-1.929292090055312*nuVtSqSum[0]*fr[19]-1.929292090055312*nuVtSqSum[0]*fl[19]+3.866990209613929*nuVtSqSum[3]*fr[17]-3.866990209613929*nuVtSqSum[3]*fl[17]+4.39754237117165*nuVtSqSum[1]*fr[15]-4.39754237117165*nuVtSqSum[1]*fl[15]-5.473078644031159*nuVtSqSum[2]*fr[13]-5.473078644031159*nuVtSqSum[2]*fl[13]+4.397542371171649*nuVtSqSum[0]*fr[9]-4.397542371171649*nuVtSqSum[0]*fl[9]+3.866990209613929*nuVtSqSum[2]*fr[7]-3.866990209613929*nuVtSqSum[2]*fl[7]-5.473078644031159*nuVtSqSum[1]*fr[5]-5.473078644031159*nuVtSqSum[1]*fl[5]-5.473078644031159*nuVtSqSum[0]*fr[3]-5.473078644031159*nuVtSqSum[0]*fl[3]+3.866990209613929*fr[1]*nuVtSqSum[1]-3.866990209613929*fl[1]*nuVtSqSum[1]+3.866990209613929*fr[0]*nuVtSqSum[0]-3.866990209613929*fl[0]*nuVtSqSum[0])*rdv+alphaDrag[1]*(0.9354143466934852*favg[27]+0.7905694150420948*favg[15]+0.6123724356957944*favg[5]+0.3535533905932737*favg[1])+alphaDrag[3]*(0.6123724356957942*favg[25]+0.3535533905932737*favg[17])-1.322875655532295*fjump[19]+alphaDrag[0]*(0.9354143466934851*favg[19]+0.7905694150420947*favg[9]+0.6123724356957944*favg[3]+0.3535533905932737*favg[0])+alphaDrag[2]*(0.6123724356957944*favg[13]+0.3535533905932737*favg[7])-1.118033988749895*fjump[9]-0.8660254037844386*fjump[3]-0.5*fjump[0]; 
  Ghat[1] = ((-1.72561130472653*nuVtSqSum[2]*fr[27])-1.929292090055312*nuVtSqSum[0]*fr[27]-1.72561130472653*nuVtSqSum[2]*fl[27]-1.929292090055312*nuVtSqSum[0]*fl[27]-4.80706006316676*nuVtSqSum[2]*fr[25]-4.80706006316676*nuVtSqSum[2]*fl[25]-1.929292090055312*nuVtSqSum[1]*fr[19]-1.929292090055312*nuVtSqSum[1]*fl[19]+3.396416424888148*nuVtSqSum[2]*fr[17]-3.396416424888148*nuVtSqSum[2]*fl[17]+3.933281470350169*nuVtSqSum[2]*fr[15]+4.39754237117165*nuVtSqSum[0]*fr[15]-3.933281470350169*nuVtSqSum[2]*fl[15]-4.39754237117165*nuVtSqSum[0]*fl[15]-4.807060063166761*nuVtSqSum[3]*fr[13]-4.89527035770242*nuVtSqSum[1]*fr[13]-4.807060063166761*nuVtSqSum[3]*fl[13]-4.89527035770242*nuVtSqSum[1]*fl[13]+4.397542371171649*nuVtSqSum[1]*fr[9]-4.397542371171649*nuVtSqSum[1]*fl[9]+3.396416424888148*nuVtSqSum[3]*fr[7]+3.458741190809164*nuVtSqSum[1]*fr[7]-3.396416424888148*nuVtSqSum[3]*fl[7]-3.458741190809164*nuVtSqSum[1]*fl[7]-4.89527035770242*nuVtSqSum[2]*fr[5]-5.473078644031159*nuVtSqSum[0]*fr[5]-4.89527035770242*nuVtSqSum[2]*fl[5]-5.473078644031159*nuVtSqSum[0]*fl[5]-5.473078644031159*nuVtSqSum[1]*fr[3]-5.473078644031159*nuVtSqSum[1]*fl[3]+3.458741190809164*fr[1]*nuVtSqSum[2]-3.458741190809164*fl[1]*nuVtSqSum[2]+3.866990209613929*fr[0]*nuVtSqSum[1]-3.866990209613929*fl[0]*nuVtSqSum[1]+3.866990209613929*nuVtSqSum[0]*fr[1]-3.866990209613929*nuVtSqSum[0]*fl[1])*rdv-1.322875655532295*fjump[27]+alphaDrag[0]*(0.9354143466934852*favg[27]+0.7905694150420948*favg[15]+0.6123724356957944*favg[5]+0.3535533905932737*favg[1])+alphaDrag[2]*(0.8366600265340755*favg[27]+0.5378528742004768*favg[25]+0.3105295017040592*favg[17]+0.7071067811865475*favg[15]+0.5477225575051661*favg[5]+0.3162277660168379*favg[1])+alphaDrag[1]*(0.9354143466934851*favg[19]+0.5477225575051661*favg[13]+0.7905694150420947*favg[9]+0.3162277660168379*favg[7]+0.6123724356957944*favg[3]+0.3535533905932737*favg[0])-1.118033988749895*fjump[15]+alphaDrag[3]*(0.5378528742004769*favg[13]+0.3105295017040592*favg[7])-0.8660254037844386*fjump[5]-0.5*fjump[1]; 
  Ghat[2] = ((-1.929292090055312*nuVtSqSum[1]*fr[31])-1.929292090055312*nuVtSqSum[1]*fl[31]-5.473078644031159*nuVtSqSum[3]*fr[29]-5.473078644031159*nuVtSqSum[3]*fl[29]-1.929292090055312*nuVtSqSum[0]*fr[28]-1.929292090055312*nuVtSqSum[0]*fl[28]+3.86699020961393*nuVtSqSum[3]*fr[23]-3.86699020961393*nuVtSqSum[3]*fl[23]+4.397542371171649*nuVtSqSum[1]*fr[22]-4.397542371171649*nuVtSqSum[1]*fl[22]-5.473078644031159*nuVtSqSum[2]*fr[20]-5.473078644031159*nuVtSqSum[2]*fl[20]+4.39754237117165*nuVtSqSum[0]*fr[16]-4.39754237117165*nuVtSqSum[0]*fl[16]+3.86699020961393*nuVtSqSum[2]*fr[11]-3.86699020961393*nuVtSqSum[2]*fl[11]-5.473078644031159*nuVtSqSum[1]*fr[10]-5.473078644031159*nuVtSqSum[1]*fl[10]-5.473078644031159*nuVtSqSum[0]*fr[6]-5.473078644031159*nuVtSqSum[0]*fl[6]+3.866990209613929*nuVtSqSum[1]*fr[4]-3.866990209613929*nuVtSqSum[1]*fl[4]+3.866990209613929*nuVtSqSum[0]*fr[2]-3.866990209613929*nuVtSqSum[0]*fl[2])*rdv+alphaDrag[1]*(0.9354143466934851*favg[31]+0.7905694150420947*favg[22]+0.6123724356957944*favg[10]+0.3535533905932737*favg[4])+alphaDrag[3]*(0.6123724356957944*favg[29]+0.3535533905932737*favg[23])-1.322875655532295*fjump[28]+alphaDrag[0]*(0.9354143466934852*favg[28]+0.7905694150420948*favg[16]+0.6123724356957944*favg[6]+0.3535533905932737*favg[2])+alphaDrag[2]*(0.6123724356957944*favg[20]+0.3535533905932737*favg[11])-1.118033988749895*fjump[16]-0.8660254037844386*fjump[6]-0.5*fjump[2]; 
  Ghat[4] = ((-1.72561130472653*nuVtSqSum[2]*fr[31])-1.929292090055312*nuVtSqSum[0]*fr[31]-1.72561130472653*nuVtSqSum[2]*fl[31]-1.929292090055312*nuVtSqSum[0]*fl[31]-4.807060063166761*nuVtSqSum[2]*fr[29]-4.807060063166761*nuVtSqSum[2]*fl[29]-1.929292090055312*nuVtSqSum[1]*fr[28]-1.929292090055312*nuVtSqSum[1]*fl[28]+3.396416424888148*nuVtSqSum[2]*fr[23]-3.396416424888148*nuVtSqSum[2]*fl[23]+3.933281470350169*nuVtSqSum[2]*fr[22]+4.397542371171649*nuVtSqSum[0]*fr[22]-3.933281470350169*nuVtSqSum[2]*fl[22]-4.397542371171649*nuVtSqSum[0]*fl[22]-4.807060063166761*nuVtSqSum[3]*fr[20]-4.89527035770242*nuVtSqSum[1]*fr[20]-4.807060063166761*nuVtSqSum[3]*fl[20]-4.89527035770242*nuVtSqSum[1]*fl[20]+4.39754237117165*nuVtSqSum[1]*fr[16]-4.39754237117165*nuVtSqSum[1]*fl[16]+3.396416424888148*nuVtSqSum[3]*fr[11]+3.458741190809164*nuVtSqSum[1]*fr[11]-3.396416424888148*nuVtSqSum[3]*fl[11]-3.458741190809164*nuVtSqSum[1]*fl[11]-4.89527035770242*nuVtSqSum[2]*fr[10]-5.473078644031159*nuVtSqSum[0]*fr[10]-4.89527035770242*nuVtSqSum[2]*fl[10]-5.473078644031159*nuVtSqSum[0]*fl[10]-5.473078644031159*nuVtSqSum[1]*fr[6]-5.473078644031159*nuVtSqSum[1]*fl[6]+3.458741190809164*nuVtSqSum[2]*fr[4]+3.866990209613929*nuVtSqSum[0]*fr[4]-3.458741190809164*nuVtSqSum[2]*fl[4]-3.866990209613929*nuVtSqSum[0]*fl[4]+3.866990209613929*nuVtSqSum[1]*fr[2]-3.866990209613929*nuVtSqSum[1]*fl[2])*rdv-1.322875655532295*fjump[31]+alphaDrag[0]*(0.9354143466934851*favg[31]+0.7905694150420947*favg[22]+0.6123724356957944*favg[10]+0.3535533905932737*favg[4])+alphaDrag[2]*(0.8366600265340755*favg[31]+0.537852874200477*favg[29]+0.3105295017040593*favg[23]+0.7071067811865475*favg[22]+0.5477225575051661*favg[10]+0.3162277660168379*favg[4])+alphaDrag[1]*(0.9354143466934852*favg[28]+0.5477225575051661*favg[20]+0.7905694150420948*favg[16]+0.3162277660168379*favg[11]+0.6123724356957944*favg[6]+0.3535533905932737*favg[2])-1.118033988749895*fjump[22]+alphaDrag[3]*(0.537852874200477*favg[20]+0.3105295017040593*favg[11])-0.8660254037844386*fjump[10]-0.5*fjump[4]; 
  Ghat[7] = ((-1.694516662281606*nuVtSqSum[3]*fr[27])-1.72561130472653*nuVtSqSum[1]*fr[27]-1.694516662281606*nuVtSqSum[3]*fl[27]-1.72561130472653*nuVtSqSum[1]*fl[27]-3.263513571801613*nuVtSqSum[3]*fr[25]-4.80706006316676*nuVtSqSum[1]*fr[25]-3.263513571801613*nuVtSqSum[3]*fl[25]-4.80706006316676*nuVtSqSum[1]*fl[25]-1.929292090055312*nuVtSqSum[2]*fr[19]-1.929292090055312*nuVtSqSum[2]*fl[19]+2.305827460539443*nuVtSqSum[3]*fr[17]+3.396416424888148*nuVtSqSum[1]*fr[17]-2.305827460539443*nuVtSqSum[3]*fl[17]-3.396416424888148*nuVtSqSum[1]*fl[17]+3.86240572873861*nuVtSqSum[3]*fr[15]+3.933281470350169*nuVtSqSum[1]*fr[15]-3.86240572873861*nuVtSqSum[3]*fl[15]-3.933281470350169*nuVtSqSum[1]*fl[15]-3.496621684073157*nuVtSqSum[2]*fr[13]-5.473078644031159*nuVtSqSum[0]*fr[13]-3.496621684073157*nuVtSqSum[2]*fl[13]-5.473078644031159*nuVtSqSum[0]*fl[13]+4.397542371171649*nuVtSqSum[2]*fr[9]-4.397542371171649*nuVtSqSum[2]*fl[9]+2.470529422006546*nuVtSqSum[2]*fr[7]+3.866990209613929*nuVtSqSum[0]*fr[7]-2.470529422006546*nuVtSqSum[2]*fl[7]-3.866990209613929*nuVtSqSum[0]*fl[7]-4.807060063166761*nuVtSqSum[3]*fr[5]-4.89527035770242*nuVtSqSum[1]*fr[5]-4.807060063166761*nuVtSqSum[3]*fl[5]-4.89527035770242*nuVtSqSum[1]*fl[5]+3.396416424888148*fr[1]*nuVtSqSum[3]-3.396416424888148*fl[1]*nuVtSqSum[3]-5.473078644031159*nuVtSqSum[2]*fr[3]-5.473078644031159*nuVtSqSum[2]*fl[3]+3.866990209613929*fr[0]*nuVtSqSum[2]-3.866990209613929*fl[0]*nuVtSqSum[2]+3.458741190809164*fr[1]*nuVtSqSum[1]-3.458741190809164*fl[1]*nuVtSqSum[1])*rdv+alphaDrag[1]*(0.8366600265340755*favg[27]+0.5378528742004768*favg[25]+0.3105295017040592*favg[17]+0.7071067811865475*favg[15]+0.5477225575051661*favg[5]+0.3162277660168379*favg[1])+alphaDrag[3]*(0.8215838362577488*favg[27]+0.3651483716701107*favg[25]+0.210818510677892*favg[17]+0.6943650748294133*favg[15]+0.537852874200477*favg[5]+0.3105295017040592*favg[1])+alphaDrag[2]*(0.9354143466934851*favg[19]+0.3912303982179757*favg[13]+0.7905694150420947*favg[9]+0.2258769757263128*favg[7]+0.6123724356957944*favg[3]+0.3535533905932737*favg[0])-0.8660254037844387*fjump[13]+alphaDrag[0]*(0.6123724356957944*favg[13]+0.3535533905932737*favg[7])-0.5*fjump[7]; 
  Ghat[8] = ((-5.473078644031159*nuVtSqSum[1]*fr[21])-5.473078644031159*nuVtSqSum[1]*fl[21]-5.473078644031159*nuVtSqSum[0]*fr[14]-5.473078644031159*nuVtSqSum[0]*fl[14]+3.86699020961393*nuVtSqSum[1]*fr[12]-3.86699020961393*nuVtSqSum[1]*fl[12]+3.866990209613929*nuVtSqSum[0]*fr[8]-3.866990209613929*nuVtSqSum[0]*fl[8])*rdv+alphaDrag[1]*(0.6123724356957944*favg[21]+0.3535533905932737*favg[12])-0.8660254037844387*fjump[14]+alphaDrag[0]*(0.6123724356957944*favg[14]+0.3535533905932737*favg[8])-0.5*fjump[8]; 
  Ghat[11] = ((-1.694516662281607*nuVtSqSum[3]*fr[31])-1.72561130472653*nuVtSqSum[1]*fr[31]-1.694516662281607*nuVtSqSum[3]*fl[31]-1.72561130472653*nuVtSqSum[1]*fl[31]-3.263513571801613*nuVtSqSum[3]*fr[29]-4.807060063166761*nuVtSqSum[1]*fr[29]-3.263513571801613*nuVtSqSum[3]*fl[29]-4.807060063166761*nuVtSqSum[1]*fl[29]-1.929292090055312*nuVtSqSum[2]*fr[28]-1.929292090055312*nuVtSqSum[2]*fl[28]+2.305827460539442*nuVtSqSum[3]*fr[23]+3.396416424888147*nuVtSqSum[1]*fr[23]-2.305827460539442*nuVtSqSum[3]*fl[23]-3.396416424888147*nuVtSqSum[1]*fl[23]+3.86240572873861*nuVtSqSum[3]*fr[22]+3.933281470350169*nuVtSqSum[1]*fr[22]-3.86240572873861*nuVtSqSum[3]*fl[22]-3.933281470350169*nuVtSqSum[1]*fl[22]-3.496621684073157*nuVtSqSum[2]*fr[20]-5.473078644031159*nuVtSqSum[0]*fr[20]-3.496621684073157*nuVtSqSum[2]*fl[20]-5.473078644031159*nuVtSqSum[0]*fl[20]+4.397542371171649*nuVtSqSum[2]*fr[16]-4.397542371171649*nuVtSqSum[2]*fl[16]+2.470529422006546*nuVtSqSum[2]*fr[11]+3.866990209613929*nuVtSqSum[0]*fr[11]-2.470529422006546*nuVtSqSum[2]*fl[11]-3.866990209613929*nuVtSqSum[0]*fl[11]-4.807060063166761*nuVtSqSum[3]*fr[10]-4.89527035770242*nuVtSqSum[1]*fr[10]-4.807060063166761*nuVtSqSum[3]*fl[10]-4.89527035770242*nuVtSqSum[1]*fl[10]-5.473078644031159*nuVtSqSum[2]*fr[6]-5.473078644031159*nuVtSqSum[2]*fl[6]+3.396416424888148*nuVtSqSum[3]*fr[4]+3.458741190809164*nuVtSqSum[1]*fr[4]-3.396416424888148*nuVtSqSum[3]*fl[4]-3.458741190809164*nuVtSqSum[1]*fl[4]+3.86699020961393*fr[2]*nuVtSqSum[2]-3.86699020961393*fl[2]*nuVtSqSum[2])*rdv+alphaDrag[1]*(0.8366600265340757*favg[31]+0.5378528742004769*favg[29]+0.3105295017040593*favg[23]+0.7071067811865475*favg[22]+0.5477225575051661*favg[10]+0.3162277660168379*favg[4])+alphaDrag[3]*(0.821583836257749*favg[31]+0.3651483716701107*favg[29]+0.2108185106778919*favg[23]+0.6943650748294133*favg[22]+0.5378528742004769*favg[10]+0.3105295017040593*favg[4])+alphaDrag[2]*(0.9354143466934851*favg[28]+0.3912303982179757*favg[20]+0.7905694150420947*favg[16]+0.2258769757263128*favg[11]+0.6123724356957944*favg[6]+0.3535533905932737*favg[2])-0.8660254037844387*fjump[20]+alphaDrag[0]*(0.6123724356957944*favg[20]+0.3535533905932737*favg[11])-0.5*fjump[11]; 
  Ghat[12] = ((-4.89527035770242*nuVtSqSum[2]*fr[21])-5.473078644031159*nuVtSqSum[0]*fr[21]-4.89527035770242*nuVtSqSum[2]*fl[21]-5.473078644031159*nuVtSqSum[0]*fl[21]-5.473078644031159*nuVtSqSum[1]*fr[14]-5.473078644031159*nuVtSqSum[1]*fl[14]+3.458741190809164*nuVtSqSum[2]*fr[12]+3.866990209613929*nuVtSqSum[0]*fr[12]-3.458741190809164*nuVtSqSum[2]*fl[12]-3.866990209613929*nuVtSqSum[0]*fl[12]+3.86699020961393*nuVtSqSum[1]*fr[8]-3.86699020961393*nuVtSqSum[1]*fl[8])*rdv-0.8660254037844387*fjump[21]+alphaDrag[0]*(0.6123724356957944*favg[21]+0.3535533905932737*favg[12])+alphaDrag[2]*(0.5477225575051661*favg[21]+0.3162277660168379*favg[12])+alphaDrag[1]*(0.6123724356957944*favg[14]+0.3535533905932737*favg[8])-0.5*fjump[12]; 
  Ghat[17] = ((-1.694516662281606*nuVtSqSum[2]*fr[27])-1.694516662281606*nuVtSqSum[2]*fl[27]-3.263513571801613*nuVtSqSum[2]*fr[25]-5.473078644031158*nuVtSqSum[0]*fr[25]-3.263513571801613*nuVtSqSum[2]*fl[25]-5.473078644031158*nuVtSqSum[0]*fl[25]-1.929292090055312*nuVtSqSum[3]*fr[19]-1.929292090055312*nuVtSqSum[3]*fl[19]+2.305827460539443*nuVtSqSum[2]*fr[17]+3.866990209613929*nuVtSqSum[0]*fr[17]-2.305827460539443*nuVtSqSum[2]*fl[17]-3.866990209613929*nuVtSqSum[0]*fl[17]+3.86240572873861*nuVtSqSum[2]*fr[15]-3.86240572873861*nuVtSqSum[2]*fl[15]-3.263513571801613*nuVtSqSum[3]*fr[13]-4.807060063166761*nuVtSqSum[1]*fr[13]-3.263513571801613*nuVtSqSum[3]*fl[13]-4.807060063166761*nuVtSqSum[1]*fl[13]+4.397542371171649*nuVtSqSum[3]*fr[9]-4.397542371171649*nuVtSqSum[3]*fl[9]+2.305827460539443*nuVtSqSum[3]*fr[7]+3.396416424888148*nuVtSqSum[1]*fr[7]-2.305827460539443*nuVtSqSum[3]*fl[7]-3.396416424888148*nuVtSqSum[1]*fl[7]-4.807060063166761*nuVtSqSum[2]*fr[5]-4.807060063166761*nuVtSqSum[2]*fl[5]-5.473078644031159*fr[3]*nuVtSqSum[3]-5.473078644031159*fl[3]*nuVtSqSum[3]+3.866990209613929*fr[0]*nuVtSqSum[3]-3.866990209613929*fl[0]*nuVtSqSum[3]+3.396416424888148*fr[1]*nuVtSqSum[2]-3.396416424888148*fl[1]*nuVtSqSum[2])*rdv+alphaDrag[2]*(0.8215838362577488*favg[27]+0.3651483716701107*favg[25]+0.210818510677892*favg[17]+0.6943650748294133*favg[15]+0.537852874200477*favg[5]+0.3105295017040592*favg[1])-0.8660254037844386*fjump[25]+alphaDrag[0]*(0.6123724356957942*favg[25]+0.3535533905932737*favg[17])+alphaDrag[3]*(0.9354143466934851*favg[19]+0.3651483716701107*favg[13]+0.7905694150420947*favg[9]+0.210818510677892*favg[7]+0.6123724356957944*favg[3]+0.3535533905932737*favg[0])-0.5*fjump[17]+alphaDrag[1]*(0.5378528742004769*favg[13]+0.3105295017040592*favg[7]); 
  Ghat[18] = ((-5.473078644031159*nuVtSqSum[1]*fr[30])-5.473078644031159*nuVtSqSum[1]*fl[30]-5.473078644031158*nuVtSqSum[0]*fr[26]-5.473078644031158*nuVtSqSum[0]*fl[26]+3.86699020961393*nuVtSqSum[1]*fr[24]-3.86699020961393*nuVtSqSum[1]*fl[24]+3.866990209613929*nuVtSqSum[0]*fr[18]-3.866990209613929*nuVtSqSum[0]*fl[18])*rdv+alphaDrag[1]*(0.6123724356957944*favg[30]+0.3535533905932737*favg[24])-0.8660254037844386*fjump[26]+alphaDrag[0]*(0.6123724356957942*favg[26]+0.3535533905932737*favg[18])-0.5*fjump[18]; 
  Ghat[23] = ((-1.694516662281606*nuVtSqSum[2]*fr[31])-1.694516662281606*nuVtSqSum[2]*fl[31]-3.263513571801613*nuVtSqSum[2]*fr[29]-5.473078644031158*nuVtSqSum[0]*fr[29]-3.263513571801613*nuVtSqSum[2]*fl[29]-5.473078644031158*nuVtSqSum[0]*fl[29]-1.929292090055312*nuVtSqSum[3]*fr[28]-1.929292090055312*nuVtSqSum[3]*fl[28]+2.305827460539443*nuVtSqSum[2]*fr[23]+3.866990209613929*nuVtSqSum[0]*fr[23]-2.305827460539443*nuVtSqSum[2]*fl[23]-3.866990209613929*nuVtSqSum[0]*fl[23]+3.86240572873861*nuVtSqSum[2]*fr[22]-3.86240572873861*nuVtSqSum[2]*fl[22]-3.263513571801613*nuVtSqSum[3]*fr[20]-4.80706006316676*nuVtSqSum[1]*fr[20]-3.263513571801613*nuVtSqSum[3]*fl[20]-4.80706006316676*nuVtSqSum[1]*fl[20]+4.397542371171649*nuVtSqSum[3]*fr[16]-4.397542371171649*nuVtSqSum[3]*fl[16]+2.305827460539442*nuVtSqSum[3]*fr[11]+3.396416424888147*nuVtSqSum[1]*fr[11]-2.305827460539442*nuVtSqSum[3]*fl[11]-3.396416424888147*nuVtSqSum[1]*fl[11]-4.80706006316676*nuVtSqSum[2]*fr[10]-4.80706006316676*nuVtSqSum[2]*fl[10]-5.473078644031158*nuVtSqSum[3]*fr[6]-5.473078644031158*nuVtSqSum[3]*fl[6]+3.396416424888148*nuVtSqSum[2]*fr[4]-3.396416424888148*nuVtSqSum[2]*fl[4]+3.86699020961393*fr[2]*nuVtSqSum[3]-3.86699020961393*fl[2]*nuVtSqSum[3])*rdv+alphaDrag[2]*(0.8215838362577488*favg[31]+0.3651483716701107*favg[29]+0.210818510677892*favg[23]+0.6943650748294133*favg[22]+0.5378528742004768*favg[10]+0.3105295017040593*favg[4])-0.8660254037844386*fjump[29]+alphaDrag[0]*(0.6123724356957942*favg[29]+0.3535533905932737*favg[23])+alphaDrag[3]*(0.9354143466934851*favg[28]+0.3651483716701107*favg[20]+0.7905694150420945*favg[16]+0.2108185106778919*favg[11]+0.6123724356957942*favg[6]+0.3535533905932737*favg[2])-0.5*fjump[23]+alphaDrag[1]*(0.5378528742004768*favg[20]+0.3105295017040593*favg[11]); 
  Ghat[24] = ((-4.895270357702419*nuVtSqSum[2]*fr[30])-5.473078644031158*nuVtSqSum[0]*fr[30]-4.895270357702419*nuVtSqSum[2]*fl[30]-5.473078644031158*nuVtSqSum[0]*fl[30]-5.473078644031159*nuVtSqSum[1]*fr[26]-5.473078644031159*nuVtSqSum[1]*fl[26]+3.458741190809164*nuVtSqSum[2]*fr[24]+3.866990209613929*nuVtSqSum[0]*fr[24]-3.458741190809164*nuVtSqSum[2]*fl[24]-3.866990209613929*nuVtSqSum[0]*fl[24]+3.86699020961393*nuVtSqSum[1]*fr[18]-3.86699020961393*nuVtSqSum[1]*fl[18])*rdv-0.8660254037844386*fjump[30]+alphaDrag[0]*(0.6123724356957942*favg[30]+0.3535533905932737*favg[24])+alphaDrag[2]*(0.547722557505166*favg[30]+0.3162277660168379*favg[24])+alphaDrag[1]*(0.6123724356957944*favg[26]+0.3535533905932737*favg[18])-0.5*fjump[24]; 

  double incr1[32]; 
  incr1[0] = -0.5*Ghat[0]; 
  incr1[1] = -0.5*Ghat[1]; 
  incr1[2] = -0.5*Ghat[2]; 
  incr1[3] = 0.8660254037844386*Ghat[0]; 
  incr1[4] = -0.5*Ghat[4]; 
  incr1[5] = 0.8660254037844386*Ghat[1]; 
  incr1[6] = 0.8660254037844386*Ghat[2]; 
  incr1[7] = -0.5*Ghat[7]; 
  incr1[8] = -0.5*Ghat[8]; 
  incr1[9] = -1.118033988749895*Ghat[0]; 
  incr1[10] = 0.8660254037844386*Ghat[4]; 
  incr1[11] = -0.5*Ghat[11]; 
  incr1[12] = -0.5*Ghat[12]; 
  incr1[13] = 0.8660254037844387*Ghat[7]; 
  incr1[14] = 0.8660254037844387*Ghat[8]; 
  incr1[15] = -1.118033988749895*Ghat[1]; 
  incr1[16] = -1.118033988749895*Ghat[2]; 
  incr1[17] = -0.5*Ghat[17]; 
  incr1[18] = -0.5*Ghat[18]; 
  incr1[19] = 1.322875655532295*Ghat[0]; 
  incr1[20] = 0.8660254037844387*Ghat[11]; 
  incr1[21] = 0.8660254037844387*Ghat[12]; 
  incr1[22] = -1.118033988749895*Ghat[4]; 
  incr1[23] = -0.5*Ghat[23]; 
  incr1[24] = -0.5*Ghat[24]; 
  incr1[25] = 0.8660254037844386*Ghat[17]; 
  incr1[26] = 0.8660254037844386*Ghat[18]; 
  incr1[27] = 1.322875655532295*Ghat[1]; 
  incr1[28] = 1.322875655532295*Ghat[2]; 
  incr1[29] = 0.8660254037844386*Ghat[23]; 
  incr1[30] = 0.8660254037844386*Ghat[24]; 
  incr1[31] = 1.322875655532295*Ghat[4]; 

  double incr2[32]; 
  incr2[3] = nuVtSqSum[1]*((-0.2314550249431378*fr[27])+0.2314550249431378*fl[27]+0.4279082480509107*(fr[15]+fl[15])-0.4640388251536715*fr[5]+0.4640388251536715*fl[5]+0.3061862178478971*(fr[1]+fl[1]))+nuVtSqSum[3]*((-0.4640388251536714*fr[25])+0.4640388251536714*fl[25]+0.3061862178478971*(fr[17]+fl[17]))+nuVtSqSum[0]*((-0.2314550249431378*fr[19])+0.2314550249431378*fl[19]+0.4279082480509108*(fr[9]+fl[9])-0.4640388251536715*fr[3]+0.4640388251536715*fl[3]+0.3061862178478971*(fr[0]+fl[0]))+nuVtSqSum[2]*((-0.4640388251536715*fr[13])+0.4640388251536715*fl[13]+0.3061862178478971*(fr[7]+fl[7])); 
  incr2[5] = nuVtSqSum[2]*((-0.2070196678027062*fr[27])+0.2070196678027062*fl[27]-0.4075699709865775*fr[25]+0.4075699709865775*fl[25]+0.2689264371002384*(fr[17]+fl[17])+0.3827327723098714*(fr[15]+fl[15])-0.4150489428970995*fr[5]+0.4150489428970995*fl[5]+0.273861278752583*(fr[1]+fl[1]))+nuVtSqSum[0]*((-0.2314550249431378*fr[27])+0.2314550249431378*fl[27]+0.4279082480509107*(fr[15]+fl[15])-0.4640388251536715*fr[5]+0.4640388251536715*fl[5]+0.3061862178478971*(fr[1]+fl[1]))+nuVtSqSum[1]*((-0.2314550249431378*fr[19])+0.2314550249431378*fl[19]-0.4150489428970995*fr[13]+0.4150489428970995*fl[13]+0.4279082480509108*(fr[9]+fl[9])+0.273861278752583*(fr[7]+fl[7])-0.4640388251536715*fr[3]+0.4640388251536715*fl[3]+0.3061862178478971*(fr[0]+fl[0]))+nuVtSqSum[3]*((-0.4075699709865777*fr[13])+0.4075699709865777*fl[13]+0.2689264371002384*(fr[7]+fl[7])); 
  incr2[6] = nuVtSqSum[1]*((-0.2314550249431378*fr[31])+0.2314550249431378*fl[31]+0.4279082480509108*(fr[22]+fl[22])-0.4640388251536715*fr[10]+0.4640388251536715*fl[10]+0.3061862178478971*(fr[4]+fl[4]))+nuVtSqSum[3]*((-0.4640388251536715*fr[29])+0.4640388251536715*fl[29]+0.3061862178478971*(fr[23]+fl[23]))+nuVtSqSum[0]*((-0.2314550249431378*fr[28])+0.2314550249431378*fl[28]+0.4279082480509107*(fr[16]+fl[16])-0.4640388251536715*fr[6]+0.4640388251536715*fl[6]+0.3061862178478971*(fr[2]+fl[2]))+nuVtSqSum[2]*((-0.4640388251536715*fr[20])+0.4640388251536715*fl[20]+0.3061862178478971*(fr[11]+fl[11])); 
  incr2[9] = nuVtSqSum[1]*(0.8964214570007949*fr[27]-0.8964214570007949*fl[27]-1.65728151840597*(fr[15]+fl[15])+1.797214641813825*fr[5]-1.797214641813825*fl[5]-1.185854122563142*(fr[1]+fl[1]))+nuVtSqSum[3]*(1.797214641813825*fr[25]-1.797214641813825*fl[25]-1.185854122563142*(fr[17]+fl[17]))+nuVtSqSum[0]*(0.896421457000795*fr[19]-0.896421457000795*fl[19]-1.657281518405969*(fr[9]+fl[9])+1.797214641813825*fr[3]-1.797214641813825*fl[3]-1.185854122563142*(fr[0]+fl[0]))+nuVtSqSum[2]*(1.797214641813825*fr[13]-1.797214641813825*fl[13]-1.185854122563142*(fr[7]+fl[7])); 
  incr2[10] = nuVtSqSum[2]*((-0.2070196678027062*fr[31])+0.2070196678027062*fl[31]-0.4075699709865775*fr[29]+0.4075699709865775*fl[29]+0.2689264371002383*(fr[23]+fl[23])+0.3827327723098713*(fr[22]+fl[22])-0.4150489428970995*fr[10]+0.4150489428970995*fl[10]+0.273861278752583*(fr[4]+fl[4]))+nuVtSqSum[0]*((-0.2314550249431378*fr[31])+0.2314550249431378*fl[31]+0.4279082480509108*(fr[22]+fl[22])-0.4640388251536715*fr[10]+0.4640388251536715*fl[10]+0.3061862178478971*(fr[4]+fl[4]))+nuVtSqSum[1]*((-0.2314550249431378*fr[28])+0.2314550249431378*fl[28]-0.4150489428970995*fr[20]+0.4150489428970995*fl[20]+0.4279082480509107*(fr[16]+fl[16])+0.273861278752583*(fr[11]+fl[11])-0.4640388251536715*fr[6]+0.4640388251536715*fl[6]+0.3061862178478971*(fr[2]+fl[2]))+nuVtSqSum[3]*((-0.4075699709865775*fr[20])+0.4075699709865775*fl[20]+0.2689264371002384*(fr[11]+fl[11])); 
  incr2[13] = nuVtSqSum[3]*((-0.2032892781536815*fr[27])+0.2032892781536815*fl[27]-0.276699295264733*fr[25]+0.276699295264733*fl[25]+0.1825741858350553*(fr[17]+fl[17])+0.3758361214393465*(fr[15]+fl[15])-0.4075699709865777*fr[5]+0.4075699709865777*fl[5]+0.2689264371002384*(fr[1]+fl[1]))+nuVtSqSum[1]*((-0.2070196678027063*fr[27])+0.2070196678027063*fl[27]-0.4075699709865777*fr[25]+0.4075699709865777*fl[25]+0.2689264371002384*(fr[17]+fl[17])+0.3827327723098713*(fr[15]+fl[15])-0.4150489428970995*fr[5]+0.4150489428970995*fl[5]+0.273861278752583*(fr[1]+fl[1]))+nuVtSqSum[2]*((-0.2314550249431378*fr[19])+0.2314550249431378*fl[19]-0.2964635306407854*fr[13]+0.2964635306407854*fl[13]+0.4279082480509108*(fr[9]+fl[9])+0.1956151991089878*(fr[7]+fl[7])-0.4640388251536715*fr[3]+0.4640388251536715*fl[3]+0.3061862178478971*(fr[0]+fl[0]))+nuVtSqSum[0]*((-0.4640388251536715*fr[13])+0.4640388251536715*fl[13]+0.3061862178478971*(fr[7]+fl[7])); 
  incr2[14] = nuVtSqSum[1]*((-0.4640388251536715*fr[21])+0.4640388251536715*fl[21]+0.3061862178478971*(fr[12]+fl[12]))+nuVtSqSum[0]*((-0.4640388251536715*fr[14])+0.4640388251536715*fl[14]+0.3061862178478971*(fr[8]+fl[8])); 
  incr2[15] = nuVtSqSum[0]*(0.8964214570007949*fr[27]-0.8964214570007949*fl[27]-1.657281518405969*(fr[15]+fl[15])+1.797214641813825*fr[5]-1.797214641813825*fl[5]-1.185854122563142*(fr[1]+fl[1]))+nuVtSqSum[2]*(0.8017837257372731*fr[27]-0.8017837257372731*fl[27]+1.578511710045255*fr[25]-1.578511710045255*fl[25]-1.04154761224412*(fr[17]+fl[17])-1.482317653203927*(fr[15]+fl[15])+1.60747764370146*fr[5]-1.60747764370146*fl[5]-1.060660171779821*(fr[1]+fl[1]))+nuVtSqSum[1]*(0.8964214570007949*fr[19]-0.8964214570007949*fl[19]+1.60747764370146*fr[13]-1.60747764370146*fl[13]-1.65728151840597*(fr[9]+fl[9])-1.060660171779821*(fr[7]+fl[7])+1.797214641813825*fr[3]-1.797214641813825*fl[3]-1.185854122563142*(fr[0]+fl[0]))+nuVtSqSum[3]*(1.578511710045255*fr[13]-1.578511710045255*fl[13]-1.04154761224412*(fr[7]+fl[7])); 
  incr2[16] = nuVtSqSum[1]*(0.8964214570007949*fr[31]-0.8964214570007949*fl[31]-1.65728151840597*(fr[22]+fl[22])+1.797214641813825*fr[10]-1.797214641813825*fl[10]-1.185854122563142*(fr[4]+fl[4]))+nuVtSqSum[3]*(1.797214641813825*fr[29]-1.797214641813825*fl[29]-1.185854122563141*(fr[23]+fl[23]))+nuVtSqSum[0]*(0.8964214570007949*fr[28]-0.8964214570007949*fl[28]-1.657281518405969*(fr[16]+fl[16])+1.797214641813825*fr[6]-1.797214641813825*fl[6]-1.185854122563142*(fr[2]+fl[2]))+nuVtSqSum[2]*(1.797214641813825*fr[20]-1.797214641813825*fl[20]-1.185854122563142*(fr[11]+fl[11])); 
  incr2[19] = nuVtSqSum[1]*((-2.121320343559642*fr[27])+2.121320343559642*fl[27]+3.921843874378477*(fr[15]+fl[15])-4.252986083330156*fr[5]+4.252986083330156*fl[5]+2.806243040080455*(fr[1]+fl[1]))+nuVtSqSum[3]*((-4.252986083330155*fr[25])+4.252986083330155*fl[25]+2.806243040080455*(fr[17]+fl[17]))+nuVtSqSum[0]*((-2.121320343559642*fr[19])+2.121320343559642*fl[19]+3.921843874378478*(fr[9]+fl[9])-4.252986083330156*fr[3]+4.252986083330156*fl[3]+2.806243040080455*(fr[0]+fl[0]))+nuVtSqSum[2]*((-4.252986083330157*fr[13])+4.252986083330157*fl[13]+2.806243040080455*(fr[7]+fl[7])); 
  incr2[20] = nuVtSqSum[3]*((-0.2032892781536815*fr[31])+0.2032892781536815*fl[31]-0.2766992952647331*fr[29]+0.2766992952647331*fl[29]+0.1825741858350553*(fr[23]+fl[23])+0.3758361214393465*(fr[22]+fl[22])-0.4075699709865775*fr[10]+0.4075699709865775*fl[10]+0.2689264371002384*(fr[4]+fl[4]))+nuVtSqSum[1]*((-0.2070196678027062*fr[31])+0.2070196678027062*fl[31]-0.4075699709865775*fr[29]+0.4075699709865775*fl[29]+0.2689264371002383*(fr[23]+fl[23])+0.3827327723098713*(fr[22]+fl[22])-0.4150489428970995*fr[10]+0.4150489428970995*fl[10]+0.273861278752583*(fr[4]+fl[4]))+nuVtSqSum[2]*((-0.2314550249431378*fr[28])+0.2314550249431378*fl[28]-0.2964635306407854*fr[20]+0.2964635306407854*fl[20]+0.4279082480509108*(fr[16]+fl[16])+0.1956151991089878*(fr[11]+fl[11])-0.4640388251536715*fr[6]+0.4640388251536715*fl[6]+0.3061862178478971*(fr[2]+fl[2]))+nuVtSqSum[0]*((-0.4640388251536715*fr[20])+0.4640388251536715*fl[20]+0.3061862178478971*(fr[11]+fl[11])); 
  incr2[21] = nuVtSqSum[2]*((-0.4150489428970995*fr[21])+0.4150489428970995*fl[21]+0.273861278752583*(fr[12]+fl[12]))+nuVtSqSum[0]*((-0.4640388251536715*fr[21])+0.4640388251536715*fl[21]+0.3061862178478971*(fr[12]+fl[12]))+nuVtSqSum[1]*((-0.4640388251536715*fr[14])+0.4640388251536715*fl[14]+0.3061862178478971*(fr[8]+fl[8])); 
  incr2[22] = nuVtSqSum[0]*(0.896421457000795*fr[31]-0.896421457000795*fl[31]-1.657281518405969*(fr[22]+fl[22])+1.797214641813825*fr[10]-1.797214641813825*fl[10]-1.185854122563142*(fr[4]+fl[4]))+nuVtSqSum[2]*(0.801783725737273*fr[31]-0.801783725737273*fl[31]+1.578511710045255*fr[29]-1.578511710045255*fl[29]-1.04154761224412*(fr[23]+fl[23])-1.482317653203927*(fr[22]+fl[22])+1.60747764370146*fr[10]-1.60747764370146*fl[10]-1.060660171779821*(fr[4]+fl[4]))+nuVtSqSum[1]*(0.8964214570007949*fr[28]-0.8964214570007949*fl[28]+1.60747764370146*fr[20]-1.60747764370146*fl[20]-1.65728151840597*(fr[16]+fl[16])-1.060660171779821*(fr[11]+fl[11])+1.797214641813825*fr[6]-1.797214641813825*fl[6]-1.185854122563142*(fr[2]+fl[2]))+nuVtSqSum[3]*(1.578511710045255*fr[20]-1.578511710045255*fl[20]-1.04154761224412*(fr[11]+fl[11])); 
  incr2[25] = nuVtSqSum[2]*((-0.2032892781536815*fr[27])+0.2032892781536815*fl[27]-0.2766992952647331*fr[25]+0.2766992952647331*fl[25]+0.1825741858350553*(fr[17]+fl[17])+0.3758361214393465*(fr[15]+fl[15])-0.4075699709865775*fr[5]+0.4075699709865775*fl[5]+0.2689264371002383*(fr[1]+fl[1]))+nuVtSqSum[0]*((-0.4640388251536715*fr[25])+0.4640388251536715*fl[25]+0.3061862178478971*(fr[17]+fl[17]))+nuVtSqSum[3]*((-0.2314550249431378*fr[19])+0.2314550249431378*fl[19]-0.276699295264733*fr[13]+0.276699295264733*fl[13]+0.4279082480509108*(fr[9]+fl[9])+0.1825741858350553*(fr[7]+fl[7])-0.4640388251536714*fr[3]+0.4640388251536714*fl[3]+0.3061862178478971*(fr[0]+fl[0]))+nuVtSqSum[1]*((-0.4075699709865777*fr[13])+0.4075699709865777*fl[13]+0.2689264371002383*(fr[7]+fl[7])); 
  incr2[26] = nuVtSqSum[1]*((-0.4640388251536714*fr[30])+0.4640388251536714*fl[30]+0.3061862178478971*(fr[24]+fl[24]))+nuVtSqSum[0]*((-0.4640388251536715*fr[26])+0.4640388251536715*fl[26]+0.3061862178478971*(fr[18]+fl[18])); 
  incr2[27] = nuVtSqSum[2]*((-1.897366596101028*fr[27])+1.897366596101028*fl[27]-3.735440486073895*fr[25]+3.735440486073895*fl[25]+2.464751508773247*(fr[17]+fl[17])+3.507803800100569*(fr[15]+fl[15])-3.803986395874725*fr[5]+3.803986395874725*fl[5]+2.509980079602226*(fr[1]+fl[1]))+nuVtSqSum[0]*((-2.121320343559642*fr[27])+2.121320343559642*fl[27]+3.921843874378477*(fr[15]+fl[15])-4.252986083330155*fr[5]+4.252986083330155*fl[5]+2.806243040080455*(fr[1]+fl[1]))+nuVtSqSum[1]*((-2.121320343559642*fr[19])+2.121320343559642*fl[19]-3.803986395874726*fr[13]+3.803986395874726*fl[13]+3.921843874378477*(fr[9]+fl[9])+2.509980079602226*(fr[7]+fl[7])-4.252986083330155*fr[3]+4.252986083330155*fl[3]+2.806243040080455*(fr[0]+fl[0]))+nuVtSqSum[3]*((-3.735440486073896*fr[13])+3.735440486073896*fl[13]+2.464751508773247*(fr[7]+fl[7])); 
  incr2[28] = nuVtSqSum[1]*((-2.121320343559642*fr[31])+2.121320343559642*fl[31]+3.921843874378477*(fr[22]+fl[22])-4.252986083330155*fr[10]+4.252986083330155*fl[10]+2.806243040080455*(fr[4]+fl[4]))+nuVtSqSum[3]*((-4.252986083330155*fr[29])+4.252986083330155*fl[29]+2.806243040080455*(fr[23]+fl[23]))+nuVtSqSum[0]*((-2.121320343559642*fr[28])+2.121320343559642*fl[28]+3.921843874378477*(fr[16]+fl[16])-4.252986083330155*fr[6]+4.252986083330155*fl[6]+2.806243040080455*(fr[2]+fl[2]))+nuVtSqSum[2]*((-4.252986083330155*fr[20])+4.252986083330155*fl[20]+2.806243040080455*(fr[11]+fl[11])); 
  incr2[29] = nuVtSqSum[2]*((-0.2032892781536815*fr[31])+0.2032892781536815*fl[31]-0.2766992952647331*fr[29]+0.2766992952647331*fl[29]+0.1825741858350553*(fr[23]+fl[23])+0.3758361214393465*(fr[22]+fl[22])-0.4075699709865775*fr[10]+0.4075699709865775*fl[10]+0.2689264371002384*(fr[4]+fl[4]))+nuVtSqSum[0]*((-0.4640388251536715*fr[29])+0.4640388251536715*fl[29]+0.306186217847897*(fr[23]+fl[23]))+nuVtSqSum[3]*((-0.2314550249431378*fr[28])+0.2314550249431378*fl[28]-0.2766992952647331*fr[20]+0.2766992952647331*fl[20]+0.4279082480509108*(fr[16]+fl[16])+0.1825741858350553*(fr[11]+fl[11])-0.4640388251536715*fr[6]+0.4640388251536715*fl[6]+0.3061862178478971*(fr[2]+fl[2]))+nuVtSqSum[1]*((-0.4075699709865775*fr[20])+0.4075699709865775*fl[20]+0.2689264371002384*(fr[11]+fl[11])); 
  incr2[30] = nuVtSqSum[2]*((-0.4150489428970995*fr[30])+0.4150489428970995*fl[30]+0.2738612787525829*(fr[24]+fl[24]))+nuVtSqSum[0]*((-0.4640388251536715*fr[30])+0.4640388251536715*fl[30]+0.3061862178478971*(fr[24]+fl[24]))+nuVtSqSum[1]*((-0.4640388251536714*fr[26])+0.4640388251536714*fl[26]+0.3061862178478971*(fr[18]+fl[18])); 
  incr2[31] = nuVtSqSum[2]*((-1.897366596101028*fr[31])+1.897366596101028*fl[31]-3.735440486073895*fr[29]+3.735440486073895*fl[29]+2.464751508773247*(fr[23]+fl[23])+3.507803800100568*(fr[22]+fl[22])-3.803986395874726*fr[10]+3.803986395874726*fl[10]+2.509980079602226*(fr[4]+fl[4]))+nuVtSqSum[0]*((-2.121320343559642*fr[31])+2.121320343559642*fl[31]+3.921843874378478*(fr[22]+fl[22])-4.252986083330156*fr[10]+4.252986083330156*fl[10]+2.806243040080455*(fr[4]+fl[4]))+nuVtSqSum[1]*((-2.121320343559642*fr[28])+2.121320343559642*fl[28]-3.803986395874726*fr[20]+3.803986395874726*fl[20]+3.921843874378477*(fr[16]+fl[16])+2.509980079602227*(fr[11]+fl[11])-4.252986083330156*fr[6]+4.252986083330156*fl[6]+2.806243040080455*(fr[2]+fl[2]))+nuVtSqSum[3]*((-3.735440486073895*fr[20])+3.735440486073895*fl[20]+2.464751508773247*(fr[11]+fl[11])); 

  outr[0] += incr1[0]*rdv2R; 
  outr[1] += incr1[1]*rdv2R; 
  outr[2] += incr1[2]*rdv2R; 
  outr[3] += incr2[3]*rdvSq4R+incr1[3]*rdv2R; 
  outr[4] += incr1[4]*rdv2R; 
  outr[5] += incr2[5]*rdvSq4R+incr1[5]*rdv2R; 
  outr[6] += incr2[6]*rdvSq4R+incr1[6]*rdv2R; 
  outr[7] += incr1[7]*rdv2R; 
  outr[8] += incr1[8]*rdv2R; 
  outr[9] += incr2[9]*rdvSq4R+incr1[9]*rdv2R; 
  outr[10] += incr2[10]*rdvSq4R+incr1[10]*rdv2R; 
  outr[11] += incr1[11]*rdv2R; 
  outr[12] += incr1[12]*rdv2R; 
  outr[13] += incr2[13]*rdvSq4R+incr1[13]*rdv2R; 
  outr[14] += incr2[14]*rdvSq4R+incr1[14]*rdv2R; 
  outr[15] += incr2[15]*rdvSq4R+incr1[15]*rdv2R; 
  outr[16] += incr2[16]*rdvSq4R+incr1[16]*rdv2R; 
  outr[17] += incr1[17]*rdv2R; 
  outr[18] += incr1[18]*rdv2R; 
  outr[19] += incr2[19]*rdvSq4R+incr1[19]*rdv2R; 
  outr[20] += incr2[20]*rdvSq4R+incr1[20]*rdv2R; 
  outr[21] += incr2[21]*rdvSq4R+incr1[21]*rdv2R; 
  outr[22] += incr2[22]*rdvSq4R+incr1[22]*rdv2R; 
  outr[23] += incr1[23]*rdv2R; 
  outr[24] += incr1[24]*rdv2R; 
  outr[25] += incr2[25]*rdvSq4R+incr1[25]*rdv2R; 
  outr[26] += incr2[26]*rdvSq4R+incr1[26]*rdv2R; 
  outr[27] += incr2[27]*rdvSq4R+incr1[27]*rdv2R; 
  outr[28] += incr2[28]*rdvSq4R+incr1[28]*rdv2R; 
  outr[29] += incr2[29]*rdvSq4R+incr1[29]*rdv2R; 
  outr[30] += incr2[30]*rdvSq4R+incr1[30]*rdv2R; 
  outr[31] += incr2[31]*rdvSq4R+incr1[31]*rdv2R; 

  outl[0] += -1.0*incr1[0]*rdv2L; 
  outl[1] += -1.0*incr1[1]*rdv2L; 
  outl[2] += -1.0*incr1[2]*rdv2L; 
  outl[3] += incr1[3]*rdv2L-1.0*incr2[3]*rdvSq4L; 
  outl[4] += -1.0*incr1[4]*rdv2L; 
  outl[5] += incr1[5]*rdv2L-1.0*incr2[5]*rdvSq4L; 
  outl[6] += incr1[6]*rdv2L-1.0*incr2[6]*rdvSq4L; 
  outl[7] += -1.0*incr1[7]*rdv2L; 
  outl[8] += -1.0*incr1[8]*rdv2L; 
  outl[9] += incr2[9]*rdvSq4L-1.0*incr1[9]*rdv2L; 
  outl[10] += incr1[10]*rdv2L-1.0*incr2[10]*rdvSq4L; 
  outl[11] += -1.0*incr1[11]*rdv2L; 
  outl[12] += -1.0*incr1[12]*rdv2L; 
  outl[13] += incr1[13]*rdv2L-1.0*incr2[13]*rdvSq4L; 
  outl[14] += incr1[14]*rdv2L-1.0*incr2[14]*rdvSq4L; 
  outl[15] += incr2[15]*rdvSq4L-1.0*incr1[15]*rdv2L; 
  outl[16] += incr2[16]*rdvSq4L-1.0*incr1[16]*rdv2L; 
  outl[17] += -1.0*incr1[17]*rdv2L; 
  outl[18] += -1.0*incr1[18]*rdv2L; 
  outl[19] += incr1[19]*rdv2L-1.0*incr2[19]*rdvSq4L; 
  outl[20] += incr1[20]*rdv2L-1.0*incr2[20]*rdvSq4L; 
  outl[21] += incr1[21]*rdv2L-1.0*incr2[21]*rdvSq4L; 
  outl[22] += incr2[22]*rdvSq4L-1.0*incr1[22]*rdv2L; 
  outl[23] += -1.0*incr1[23]*rdv2L; 
  outl[24] += -1.0*incr1[24]*rdv2L; 
  outl[25] += incr1[25]*rdv2L-1.0*incr2[25]*rdvSq4L; 
  outl[26] += incr1[26]*rdv2L-1.0*incr2[26]*rdvSq4L; 
  outl[27] += incr1[27]*rdv2L-1.0*incr2[27]*rdvSq4L; 
  outl[28] += incr1[28]*rdv2L-1.0*incr2[28]*rdvSq4L; 
  outl[29] += incr1[29]*rdv2L-1.0*incr2[29]*rdvSq4L; 
  outl[30] += incr1[30]*rdv2L-1.0*incr2[30]*rdvSq4L; 
  outl[31] += incr1[31]*rdv2L-1.0*incr2[31]*rdvSq4L; 

  return std::abs((0.7905694150420947*sumNuUy[2])/nuSum-(0.7071067811865475*sumNuUy[0])/nuSum+wl[2]); 
} 
