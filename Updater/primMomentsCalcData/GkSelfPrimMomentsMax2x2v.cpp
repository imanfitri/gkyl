#include <PrimMomentsModDecl.h> 
 
using namespace Eigen; 
 
void GkSelfPrimMoments2x2vMax_P1(binOpData_t *data, const double *m0, const double *m1, const double *m0S, const double *m1S, const double *m2S, const double *cM, const double *cE, double *u, double *vtSq) 
{ 
  // m0,m1:       moments of the distribution function. 
  // m0S,m1S,m1S: star moments (only used for piecewise linear). 
  // cM, cE:   vtSq*cM and vtSq*cE are corrections to u and vtSq, respectively. 
  // u:        velocity. 
  // vtSq:     squared thermal speed, sqrt(T/m). 
 
  // If a corner value is below zero, use cell average m0.
  bool cellAvg = false;
  if ((-0.8660254037844386*m0[2])-0.8660254037844386*m0[1]+0.5*m0[0] < 0) { 
    cellAvg = true;
  }
  if ((-0.8660254037844386*m0[2])-0.8660254037844386*m0[1]+0.5*m0[0] < 0) { 
    cellAvg = true;
  }
  if ((-0.8660254037844386*m0[2])+0.8660254037844386*m0[1]+0.5*m0[0] < 0) { 
    cellAvg = true;
  }
  if ((-0.8660254037844386*m0[2])+0.8660254037844386*m0[1]+0.5*m0[0] < 0) { 
    cellAvg = true;
  }
 
  double m0r[3]; 
  double m1r[3]; 
  double m0Sr[3]; 
  double m1Sr[3]; 
  double m2Sr[3]; 
  if (cellAvg) { 
    m0r[0] = m0[0]; 
    m0r[1] = 0.0; 
    m0r[2] = 0.0; 
    m1r[0] = m1[0]; 
    m1r[1] = 0.0; 
    m1r[2] = 0.0; 
    m0Sr[0] = m0S[0]; 
    m0Sr[1] = 0.0; 
    m0Sr[2] = 0.0; 
    m1Sr[0] = m1S[0]; 
    m1Sr[1] = 0.0; 
    m1Sr[2] = 0.0; 
    m2Sr[0] = m2S[0]; 
    m2Sr[1] = 0.0; 
    m2Sr[2] = 0.0; 
  } else { 
    m0r[0] = m0[0]; 
    m0r[1] = m0[1]; 
    m0r[2] = m0[2]; 
    m1r[0] = m1[0]; 
    m1r[1] = m1[1]; 
    m1r[2] = m1[2]; 
    m0Sr[0] = m0S[0]; 
    m0Sr[1] = m0S[1]; 
    m0Sr[2] = m0S[2]; 
    m1Sr[0] = m1S[0]; 
    m1Sr[1] = m1S[1]; 
    m1Sr[2] = m1S[2]; 
    m2Sr[0] = m2S[0]; 
    m2Sr[1] = m2S[1]; 
    m2Sr[2] = m2S[2]; 
  } 
 
  // Declare Eigen matrix and vectors for weak division. 
  data->AEM_S = Eigen::MatrixXd::Zero(6,6); 
 
  // ....... Block from weak multiply of uX and m0  .......... // 
  data->AEM_S(0,0) = 0.5*m0r[0]; 
  data->AEM_S(0,1) = 0.5*m0r[1]; 
  data->AEM_S(0,2) = 0.5*m0r[2]; 
  data->AEM_S(1,0) = 0.5*m0r[1]; 
  data->AEM_S(1,1) = 0.5*m0r[0]; 
  data->AEM_S(2,0) = 0.5*m0r[2]; 
  data->AEM_S(2,2) = 0.5*m0r[0]; 
 
  // ....... Block from correction to uX .......... // 
  data->AEM_S(0,3) = -0.5*cM[0]; 
  data->AEM_S(0,4) = -0.5*cM[1]; 
  data->AEM_S(0,5) = -0.5*cM[2]; 
  data->AEM_S(1,3) = -0.5*cM[1]; 
  data->AEM_S(1,4) = -0.5*cM[0]; 
  data->AEM_S(2,3) = -0.5*cM[2]; 
  data->AEM_S(2,5) = -0.5*cM[0]; 
 
  // ....... Block from weak multiply of uX and m1X  .......... // 
  data->AEM_S(3,0) = 0.5*m1Sr[0]; 
  data->AEM_S(3,1) = 0.5*m1Sr[1]; 
  data->AEM_S(3,2) = 0.5*m1Sr[2]; 
  data->AEM_S(4,0) = 0.5*m1Sr[1]; 
  data->AEM_S(4,1) = 0.5*m1Sr[0]; 
  data->AEM_S(5,0) = 0.5*m1Sr[2]; 
  data->AEM_S(5,2) = 0.5*m1Sr[0]; 
 
  // ....... Block from correction to vtSq .......... // 
  data->AEM_S(3,3) = m0r[0]+0.5*m0Sr[0]-0.5*cE[0]; 
  data->AEM_S(3,4) = m0r[1]+0.5*m0Sr[1]-0.5*cE[1]; 
  data->AEM_S(3,5) = m0r[2]+0.5*m0Sr[2]-0.5*cE[2]; 
  data->AEM_S(4,3) = m0r[1]+0.5*m0Sr[1]-0.5*cE[1]; 
  data->AEM_S(4,4) = m0r[0]+0.5*m0Sr[0]-0.5*cE[0]; 
  data->AEM_S(5,3) = m0r[2]+0.5*m0Sr[2]-0.5*cE[2]; 
  data->AEM_S(5,5) = m0r[0]+0.5*m0Sr[0]-0.5*cE[0]; 
 
  // ....... RHS vector is composed of m1 and m2 .......... // 
  data->BEV_S << m1r[0],m1r[1],m1r[2],m2Sr[0],m2Sr[1],m2Sr[2]; 
 
  data->u_S = data->AEM_S.colPivHouseholderQr().solve(data->BEV_S); 
 
  Eigen::Map<VectorXd>(u,3,1) = data->u_S.segment<3>(0); 
 
  Eigen::Map<VectorXd>(vtSq,3,1) = data->u_S.segment<3>(3); 
 
} 
 
void GkSelfPrimMoments2x2vMax_P2(binOpData_t *data, const double *m0, const double *m1, const double *m2, const double *cM, const double *cE, double *u, double *vtSq) 
{ 
  // m0,m1,m2: moments of the distribution function. 
  // cM, cE:   vtSq*cM and vtSq*cE are corrections to u and vtSq, respectively. 
  // u:        velocity. 
  // vtSq:     squared thermal speed, sqrt(T/m). 
 
  // If a corner value is below zero, use cell average m0.
  bool cellAvg = false;
  if (1.118033988749895*m0[5]+1.118033988749895*m0[4]+1.5*m0[3]-0.8660254037844386*m0[2]-0.8660254037844386*m0[1]+0.5*m0[0] < 0) { 
    cellAvg = true;
  }
  if (1.118033988749895*m0[5]+1.118033988749895*m0[4]+1.5*m0[3]-0.8660254037844386*m0[2]-0.8660254037844386*m0[1]+0.5*m0[0] < 0) { 
    cellAvg = true;
  }
  if (1.118033988749895*m0[5]+1.118033988749895*m0[4]-1.5*m0[3]-0.8660254037844386*m0[2]+0.8660254037844386*m0[1]+0.5*m0[0] < 0) { 
    cellAvg = true;
  }
  if (1.118033988749895*m0[5]+1.118033988749895*m0[4]-1.5*m0[3]-0.8660254037844386*m0[2]+0.8660254037844386*m0[1]+0.5*m0[0] < 0) { 
    cellAvg = true;
  }
 
  double m0r[6]; 
  double m1r[6]; 
  double m2r[6]; 
  if (cellAvg) { 
    m0r[0] = m0[0]; 
    m0r[1] = 0.0; 
    m0r[2] = 0.0; 
    m0r[3] = 0.0; 
    m0r[4] = 0.0; 
    m0r[5] = 0.0; 
    m1r[0] = m1[0]; 
    m1r[1] = 0.0; 
    m1r[2] = 0.0; 
    m1r[3] = 0.0; 
    m1r[4] = 0.0; 
    m1r[5] = 0.0; 
    m2r[0] = m2[0]; 
    m2r[1] = 0.0; 
    m2r[2] = 0.0; 
    m2r[3] = 0.0; 
    m2r[4] = 0.0; 
    m2r[5] = 0.0; 
  } else { 
    m0r[0] = m0[0]; 
    m0r[1] = m0[1]; 
    m0r[2] = m0[2]; 
    m0r[3] = m0[3]; 
    m0r[4] = m0[4]; 
    m0r[5] = m0[5]; 
    m1r[0] = m1[0]; 
    m1r[1] = m1[1]; 
    m1r[2] = m1[2]; 
    m1r[3] = m1[3]; 
    m1r[4] = m1[4]; 
    m1r[5] = m1[5]; 
    m2r[0] = m2[0]; 
    m2r[1] = m2[1]; 
    m2r[2] = m2[2]; 
    m2r[3] = m2[3]; 
    m2r[4] = m2[4]; 
    m2r[5] = m2[5]; 
  } 
 
  // Declare Eigen matrix and vectors for weak division. 
  data->AEM_S = Eigen::MatrixXd::Zero(12,12); 
 
  // ....... Block from weak multiply of uX and m0  .......... // 
  data->AEM_S(0,0) = 0.5*m0r[0]; 
  data->AEM_S(0,1) = 0.5*m0r[1]; 
  data->AEM_S(0,2) = 0.5*m0r[2]; 
  data->AEM_S(0,3) = 0.5*m0r[3]; 
  data->AEM_S(0,4) = 0.5*m0r[4]; 
  data->AEM_S(0,5) = 0.5*m0r[5]; 
  data->AEM_S(1,0) = 0.5*m0r[1]; 
  data->AEM_S(1,1) = 0.4472135954999579*m0r[4]+0.5*m0r[0]; 
  data->AEM_S(1,2) = 0.5*m0r[3]; 
  data->AEM_S(1,3) = 0.5*m0r[2]; 
  data->AEM_S(1,4) = 0.4472135954999579*m0r[1]; 
  data->AEM_S(2,0) = 0.5*m0r[2]; 
  data->AEM_S(2,1) = 0.5*m0r[3]; 
  data->AEM_S(2,2) = 0.4472135954999579*m0r[5]+0.5*m0r[0]; 
  data->AEM_S(2,3) = 0.5*m0r[1]; 
  data->AEM_S(2,5) = 0.4472135954999579*m0r[2]; 
  data->AEM_S(3,0) = 0.5*m0r[3]; 
  data->AEM_S(3,1) = 0.5*m0r[2]; 
  data->AEM_S(3,2) = 0.5*m0r[1]; 
  data->AEM_S(3,3) = 0.4472135954999579*m0r[5]+0.4472135954999579*m0r[4]+0.5*m0r[0]; 
  data->AEM_S(3,4) = 0.4472135954999579*m0r[3]; 
  data->AEM_S(3,5) = 0.4472135954999579*m0r[3]; 
  data->AEM_S(4,0) = 0.5*m0r[4]; 
  data->AEM_S(4,1) = 0.4472135954999579*m0r[1]; 
  data->AEM_S(4,3) = 0.4472135954999579*m0r[3]; 
  data->AEM_S(4,4) = 0.31943828249997*m0r[4]+0.5*m0r[0]; 
  data->AEM_S(5,0) = 0.5*m0r[5]; 
  data->AEM_S(5,2) = 0.4472135954999579*m0r[2]; 
  data->AEM_S(5,3) = 0.4472135954999579*m0r[3]; 
  data->AEM_S(5,5) = 0.31943828249997*m0r[5]+0.5*m0r[0]; 
 
  // ....... Block from correction to uX .......... // 
  data->AEM_S(0,6) = -0.5*cM[0]; 
  data->AEM_S(0,7) = -0.5*cM[1]; 
  data->AEM_S(0,8) = -0.5*cM[2]; 
  data->AEM_S(0,9) = -0.5*cM[3]; 
  data->AEM_S(0,10) = -0.5*cM[4]; 
  data->AEM_S(0,11) = -0.5*cM[5]; 
  data->AEM_S(1,6) = -0.5*cM[1]; 
  data->AEM_S(1,7) = (-0.4472135954999579*cM[4])-0.5*cM[0]; 
  data->AEM_S(1,8) = -0.5*cM[3]; 
  data->AEM_S(1,9) = -0.5*cM[2]; 
  data->AEM_S(1,10) = -0.4472135954999579*cM[1]; 
  data->AEM_S(2,6) = -0.5*cM[2]; 
  data->AEM_S(2,7) = -0.5*cM[3]; 
  data->AEM_S(2,8) = (-0.4472135954999579*cM[5])-0.5*cM[0]; 
  data->AEM_S(2,9) = -0.5*cM[1]; 
  data->AEM_S(2,11) = -0.4472135954999579*cM[2]; 
  data->AEM_S(3,6) = -0.5*cM[3]; 
  data->AEM_S(3,7) = -0.5*cM[2]; 
  data->AEM_S(3,8) = -0.5*cM[1]; 
  data->AEM_S(3,9) = (-0.4472135954999579*cM[5])-0.4472135954999579*cM[4]-0.5*cM[0]; 
  data->AEM_S(3,10) = -0.4472135954999579*cM[3]; 
  data->AEM_S(3,11) = -0.4472135954999579*cM[3]; 
  data->AEM_S(4,6) = -0.5*cM[4]; 
  data->AEM_S(4,7) = -0.4472135954999579*cM[1]; 
  data->AEM_S(4,9) = -0.4472135954999579*cM[3]; 
  data->AEM_S(4,10) = (-0.31943828249997*cM[4])-0.5*cM[0]; 
  data->AEM_S(5,6) = -0.5*cM[5]; 
  data->AEM_S(5,8) = -0.4472135954999579*cM[2]; 
  data->AEM_S(5,9) = -0.4472135954999579*cM[3]; 
  data->AEM_S(5,11) = (-0.31943828249997*cM[5])-0.5*cM[0]; 
 
  // ....... Block from weak multiply of uX and m1X  .......... // 
  data->AEM_S(6,0) = 0.5*m1r[0]; 
  data->AEM_S(6,1) = 0.5*m1r[1]; 
  data->AEM_S(6,2) = 0.5*m1r[2]; 
  data->AEM_S(6,3) = 0.5*m1r[3]; 
  data->AEM_S(6,4) = 0.5*m1r[4]; 
  data->AEM_S(6,5) = 0.5*m1r[5]; 
  data->AEM_S(7,0) = 0.5*m1r[1]; 
  data->AEM_S(7,1) = 0.4472135954999579*m1r[4]+0.5*m1r[0]; 
  data->AEM_S(7,2) = 0.5*m1r[3]; 
  data->AEM_S(7,3) = 0.5*m1r[2]; 
  data->AEM_S(7,4) = 0.4472135954999579*m1r[1]; 
  data->AEM_S(8,0) = 0.5*m1r[2]; 
  data->AEM_S(8,1) = 0.5*m1r[3]; 
  data->AEM_S(8,2) = 0.4472135954999579*m1r[5]+0.5*m1r[0]; 
  data->AEM_S(8,3) = 0.5*m1r[1]; 
  data->AEM_S(8,5) = 0.4472135954999579*m1r[2]; 
  data->AEM_S(9,0) = 0.5*m1r[3]; 
  data->AEM_S(9,1) = 0.5*m1r[2]; 
  data->AEM_S(9,2) = 0.5*m1r[1]; 
  data->AEM_S(9,3) = 0.4472135954999579*m1r[5]+0.4472135954999579*m1r[4]+0.5*m1r[0]; 
  data->AEM_S(9,4) = 0.4472135954999579*m1r[3]; 
  data->AEM_S(9,5) = 0.4472135954999579*m1r[3]; 
  data->AEM_S(10,0) = 0.5*m1r[4]; 
  data->AEM_S(10,1) = 0.4472135954999579*m1r[1]; 
  data->AEM_S(10,3) = 0.4472135954999579*m1r[3]; 
  data->AEM_S(10,4) = 0.31943828249997*m1r[4]+0.5*m1r[0]; 
  data->AEM_S(11,0) = 0.5*m1r[5]; 
  data->AEM_S(11,2) = 0.4472135954999579*m1r[2]; 
  data->AEM_S(11,3) = 0.4472135954999579*m1r[3]; 
  data->AEM_S(11,5) = 0.31943828249997*m1r[5]+0.5*m1r[0]; 
 
  // ....... Block from correction to vtSq .......... // 
  data->AEM_S(6,6) = 1.5*m0r[0]-0.5*cE[0]; 
  data->AEM_S(6,7) = 1.5*m0r[1]-0.5*cE[1]; 
  data->AEM_S(6,8) = 1.5*m0r[2]-0.5*cE[2]; 
  data->AEM_S(6,9) = 1.5*m0r[3]-0.5*cE[3]; 
  data->AEM_S(6,10) = 1.5*m0r[4]-0.5*cE[4]; 
  data->AEM_S(6,11) = 1.5*m0r[5]-0.5*cE[5]; 
  data->AEM_S(7,6) = 1.5*m0r[1]-0.5*cE[1]; 
  data->AEM_S(7,7) = 1.341640786499874*m0r[4]-0.4472135954999579*cE[4]+1.5*m0r[0]-0.5*cE[0]; 
  data->AEM_S(7,8) = 1.5*m0r[3]-0.5*cE[3]; 
  data->AEM_S(7,9) = 1.5*m0r[2]-0.5*cE[2]; 
  data->AEM_S(7,10) = 1.341640786499874*m0r[1]-0.4472135954999579*cE[1]; 
  data->AEM_S(8,6) = 1.5*m0r[2]-0.5*cE[2]; 
  data->AEM_S(8,7) = 1.5*m0r[3]-0.5*cE[3]; 
  data->AEM_S(8,8) = 1.341640786499874*m0r[5]-0.4472135954999579*cE[5]+1.5*m0r[0]-0.5*cE[0]; 
  data->AEM_S(8,9) = 1.5*m0r[1]-0.5*cE[1]; 
  data->AEM_S(8,11) = 1.341640786499874*m0r[2]-0.4472135954999579*cE[2]; 
  data->AEM_S(9,6) = 1.5*m0r[3]-0.5*cE[3]; 
  data->AEM_S(9,7) = 1.5*m0r[2]-0.5*cE[2]; 
  data->AEM_S(9,8) = 1.5*m0r[1]-0.5*cE[1]; 
  data->AEM_S(9,9) = 1.341640786499874*m0r[5]-0.4472135954999579*cE[5]+1.341640786499874*m0r[4]-0.4472135954999579*cE[4]+1.5*m0r[0]-0.5*cE[0]; 
  data->AEM_S(9,10) = 1.341640786499874*m0r[3]-0.4472135954999579*cE[3]; 
  data->AEM_S(9,11) = 1.341640786499874*m0r[3]-0.4472135954999579*cE[3]; 
  data->AEM_S(10,6) = 1.5*m0r[4]-0.5*cE[4]; 
  data->AEM_S(10,7) = 1.341640786499874*m0r[1]-0.4472135954999579*cE[1]; 
  data->AEM_S(10,9) = 1.341640786499874*m0r[3]-0.4472135954999579*cE[3]; 
  data->AEM_S(10,10) = 0.9583148474999099*m0r[4]-0.31943828249997*cE[4]+1.5*m0r[0]-0.5*cE[0]; 
  data->AEM_S(11,6) = 1.5*m0r[5]-0.5*cE[5]; 
  data->AEM_S(11,8) = 1.341640786499874*m0r[2]-0.4472135954999579*cE[2]; 
  data->AEM_S(11,9) = 1.341640786499874*m0r[3]-0.4472135954999579*cE[3]; 
  data->AEM_S(11,11) = 0.9583148474999099*m0r[5]-0.31943828249997*cE[5]+1.5*m0r[0]-0.5*cE[0]; 
 
  // ....... RHS vector is composed of m1 and m2 .......... // 
  data->BEV_S << m1r[0],m1r[1],m1r[2],m1r[3],m1r[4],m1r[5],m2r[0],m2r[1],m2r[2],m2r[3],m2r[4],m2r[5]; 
 
  data->u_S = data->AEM_S.colPivHouseholderQr().solve(data->BEV_S); 
 
  Eigen::Map<VectorXd>(u,6,1) = data->u_S.segment<6>(0); 
 
  Eigen::Map<VectorXd>(vtSq,6,1) = data->u_S.segment<6>(6); 
 
} 
 
