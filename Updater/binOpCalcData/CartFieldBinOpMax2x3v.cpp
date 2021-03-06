#include <math.h> 
#include <CartFieldBinOpModDecl.h> 
 
using namespace Eigen; 
 
void CartFieldBinOpMultiply2x3vMax_P1(binOpData_t* data, const double *A, const double *B, const short int Ncomp, const short int eqNcomp, double *out) 
{ 
  // A:       scalar/vector field in configuration space. 
  // B:       scalar field in phase space. 
  // Ncomp:   number of components of B (should =1 here). 
  // eqNcomp: =1 if A:numComponents=B:numComponents, =0 else (should=1 here). 
  // out:     output field A*B (same number of components as B). 
 
  double tmp[6]; 
  tmp[0] = 0.5*A[2]*B[2]+0.5*A[1]*B[1]+0.5*A[0]*B[0]; 
  tmp[1] = 0.5*A[0]*B[1]+0.5*B[0]*A[1]; 
  tmp[2] = 0.5*A[0]*B[2]+0.5*B[0]*A[2]; 
  tmp[3] = 0.5*A[0]*B[3]; 
  tmp[4] = 0.5*A[0]*B[4]; 
  tmp[5] = 0.5*A[0]*B[5]; 
 
  // This tmp allows for in-place multiplication. 
  for (unsigned short int i=0; i<6; i++) 
  { 
    out[i] = tmp[i]; 
  } 
 
} 
 
void CartFieldBinOpMultiply2x3vMax_P2(binOpData_t* data, const double *A, const double *B, const short int Ncomp, const short int eqNcomp, double *out) 
{ 
  // A:       scalar/vector field in configuration space. 
  // B:       scalar field in phase space. 
  // Ncomp:   number of components of B (should =1 here). 
  // eqNcomp: =1 if A:numComponents=B:numComponents, =0 else (should=1 here). 
  // out:     output field A*B (same number of components as B). 
 
  double tmp[21]; 
  tmp[0] = 0.5*A[5]*B[17]+0.5*A[4]*B[16]+0.5*A[3]*B[6]+0.5*A[2]*B[2]+0.5*A[1]*B[1]+0.5*A[0]*B[0]; 
  tmp[1] = 0.4472135954999579*A[1]*B[16]+0.5*A[2]*B[6]+0.4472135954999579*B[1]*A[4]+0.5*B[2]*A[3]+0.5*A[0]*B[1]+0.5*B[0]*A[1]; 
  tmp[2] = 0.4472135954999579*A[2]*B[17]+0.5*A[1]*B[6]+0.4472135954999579*B[2]*A[5]+0.5*B[1]*A[3]+0.5*A[0]*B[2]+0.5*B[0]*A[2]; 
  tmp[3] = 0.5*A[2]*B[8]+0.5*A[1]*B[7]+0.5*A[0]*B[3]; 
  tmp[4] = 0.5*A[2]*B[10]+0.5*A[1]*B[9]+0.5*A[0]*B[4]; 
  tmp[5] = 0.5*A[2]*B[13]+0.5*A[1]*B[12]+0.5*A[0]*B[5]; 
  tmp[6] = 0.4472135954999579*A[3]*B[17]+0.4472135954999579*A[3]*B[16]+0.4472135954999579*A[5]*B[6]+0.4472135954999579*A[4]*B[6]+0.5*A[0]*B[6]+0.5*B[0]*A[3]+0.5*A[1]*B[2]+0.5*B[1]*A[2]; 
  tmp[7] = 0.5*A[3]*B[8]+0.4472135954999579*A[4]*B[7]+0.5*A[0]*B[7]+0.5*A[1]*B[3]; 
  tmp[8] = 0.4472135954999579*A[5]*B[8]+0.5*A[0]*B[8]+0.5*A[3]*B[7]+0.5*A[2]*B[3]; 
  tmp[9] = 0.5*A[3]*B[10]+0.4472135954999579*A[4]*B[9]+0.5*A[0]*B[9]+0.5*A[1]*B[4]; 
  tmp[10] = 0.4472135954999579*A[5]*B[10]+0.5*A[0]*B[10]+0.5*A[3]*B[9]+0.5*A[2]*B[4]; 
  tmp[11] = 0.5*A[0]*B[11]; 
  tmp[12] = 0.5*A[3]*B[13]+0.4472135954999579*A[4]*B[12]+0.5*A[0]*B[12]+0.5*A[1]*B[5]; 
  tmp[13] = 0.4472135954999579*A[5]*B[13]+0.5*A[0]*B[13]+0.5*A[3]*B[12]+0.5*A[2]*B[5]; 
  tmp[14] = 0.5*A[0]*B[14]; 
  tmp[15] = 0.5*A[0]*B[15]; 
  tmp[16] = 0.31943828249997*A[4]*B[16]+0.5*A[0]*B[16]+0.4472135954999579*A[3]*B[6]+0.5*B[0]*A[4]+0.4472135954999579*A[1]*B[1]; 
  tmp[17] = 0.31943828249997*A[5]*B[17]+0.5*A[0]*B[17]+0.4472135954999579*A[3]*B[6]+0.5*B[0]*A[5]+0.4472135954999579*A[2]*B[2]; 
  tmp[18] = 0.5*A[0]*B[18]; 
  tmp[19] = 0.5*A[0]*B[19]; 
  tmp[20] = 0.5*A[0]*B[20]; 
 
  // This tmp allows for in-place multiplication. 
  for (unsigned short int i=0; i<21; i++) 
  { 
    out[i] = tmp[i]; 
  } 
 
} 
 
void CartFieldBinOpDivide2x3vMax_P1(binOpData_t* data, const double *A, const double *B, const short int Ncomp, const short int eqNcomp, double *out) 
{ 
  // A:       configuration space denominator field (must be a scalar field). 
  // B:       phase space numerator field (must be a scalar field). 
  // Ncomp:   number of components of B (=1 here). 
  // eqNcomp: =1 if A:numComponents=B:numComponents, =0 else (=1 here). 
  // out:     output field (same number of components as B). 
 
  // If a corner value is below zero, use cell average A.
  bool avgA = false;
  if ((-0.8660254037844386*A[2])-0.8660254037844386*A[1]+0.5*A[0] < 0) { 
    avgA = true;
  }
  if ((-0.8660254037844386*A[2])-0.8660254037844386*A[1]+0.5*A[0] < 0) { 
    avgA = true;
  }
  if ((-0.8660254037844386*A[2])+0.8660254037844386*A[1]+0.5*A[0] < 0) { 
    avgA = true;
  }
  if ((-0.8660254037844386*A[2])+0.8660254037844386*A[1]+0.5*A[0] < 0) { 
    avgA = true;
  }
 
  double As[3]; 
  double Bs[6]; 
  if (avgA) { 
    As[0] = A[0]; 
    As[1] = 0.0; 
    As[2] = 0.0; 
    Bs[0] = B[0]; 
    Bs[1] = 0.0; 
    Bs[2] = 0.0; 
    Bs[3] = B[3]; 
    Bs[4] = B[4]; 
    Bs[5] = B[5]; 
  } else { 
    As[0] = A[0]; 
    As[1] = A[1]; 
    As[2] = A[2]; 
    Bs[0] = B[0]; 
    Bs[1] = B[1]; 
    Bs[2] = B[2]; 
    Bs[3] = B[3]; 
    Bs[4] = B[4]; 
    Bs[5] = B[5]; 
  } 
 
  // Fill AEM_D matrix. 
  data->AEM_D = Eigen::MatrixXd::Zero(6,6);
  data->AEM_D(0,0) = 0.5*As[0]; 
  data->AEM_D(0,1) = 0.5*As[1]; 
  data->AEM_D(0,2) = 0.5*As[2]; 
  data->AEM_D(0,3) = 0.5*As[1]; 
  data->AEM_D(0,4) = 0.5*As[0]; 
  data->AEM_D(1,0) = 0.5*As[2]; 
  data->AEM_D(1,2) = 0.5*As[0]; 
 
  // Fill BEV_D. 
  data->BEV_D << Bs[0],Bs[1],Bs[2],Bs[3],Bs[4],Bs[5]; 
 
  // Solve the system of equations. 
  data->u_D = data->AEM_D.colPivHouseholderQr().solve(data->BEV_D); 
 
  // Copy data from Eigen vector. 
  Eigen::Map<VectorXd>(out,6,1) = data->u_D; 
 
} 
 
void CartFieldBinOpDivide2x3vMax_P2(binOpData_t* data, const double *A, const double *B, const short int Ncomp, const short int eqNcomp, double *out) 
{ 
  // A:       configuration space denominator field (must be a scalar field). 
  // B:       phase space numerator field (must be a scalar field). 
  // Ncomp:   number of components of B (=1 here). 
  // eqNcomp: =1 if A:numComponents=B:numComponents, =0 else (=1 here). 
  // out:     output field (same number of components as B). 
 
  // If a corner value is below zero, use cell average A.
  bool avgA = false;
  if (1.118033988749895*A[5]+1.118033988749895*A[4]+1.5*A[3]-0.8660254037844386*A[2]-0.8660254037844386*A[1]+0.5*A[0] < 0) { 
    avgA = true;
  }
  if (1.118033988749895*A[5]+1.118033988749895*A[4]+1.5*A[3]-0.8660254037844386*A[2]-0.8660254037844386*A[1]+0.5*A[0] < 0) { 
    avgA = true;
  }
  if (1.118033988749895*A[5]+1.118033988749895*A[4]-1.5*A[3]-0.8660254037844386*A[2]+0.8660254037844386*A[1]+0.5*A[0] < 0) { 
    avgA = true;
  }
  if (1.118033988749895*A[5]+1.118033988749895*A[4]-1.5*A[3]-0.8660254037844386*A[2]+0.8660254037844386*A[1]+0.5*A[0] < 0) { 
    avgA = true;
  }
 
  double As[6]; 
  double Bs[21]; 
  if (avgA) { 
    As[0] = A[0]; 
    As[1] = 0.0; 
    As[2] = 0.0; 
    As[3] = 0.0; 
    As[4] = 0.0; 
    As[5] = 0.0; 
    Bs[0] = B[0]; 
    Bs[1] = 0.0; 
    Bs[2] = 0.0; 
    Bs[3] = B[3]; 
    Bs[4] = B[4]; 
    Bs[5] = B[5]; 
    Bs[6] = 0.0; 
    Bs[7] = 0.0; 
    Bs[8] = 0.0; 
    Bs[9] = 0.0; 
    Bs[10] = 0.0; 
    Bs[11] = B[11]; 
    Bs[12] = 0.0; 
    Bs[13] = 0.0; 
    Bs[14] = B[14]; 
    Bs[15] = B[15]; 
    Bs[16] = 0.0; 
    Bs[17] = 0.0; 
    Bs[18] = B[18]; 
    Bs[19] = B[19]; 
    Bs[20] = B[20]; 
  } else { 
    As[0] = A[0]; 
    As[1] = A[1]; 
    As[2] = A[2]; 
    As[3] = A[3]; 
    As[4] = A[4]; 
    As[5] = A[5]; 
    Bs[0] = B[0]; 
    Bs[1] = B[1]; 
    Bs[2] = B[2]; 
    Bs[3] = B[3]; 
    Bs[4] = B[4]; 
    Bs[5] = B[5]; 
    Bs[6] = B[6]; 
    Bs[7] = B[7]; 
    Bs[8] = B[8]; 
    Bs[9] = B[9]; 
    Bs[10] = B[10]; 
    Bs[11] = B[11]; 
    Bs[12] = B[12]; 
    Bs[13] = B[13]; 
    Bs[14] = B[14]; 
    Bs[15] = B[15]; 
    Bs[16] = B[16]; 
    Bs[17] = B[17]; 
    Bs[18] = B[18]; 
    Bs[19] = B[19]; 
    Bs[20] = B[20]; 
  } 
 
  // Fill AEM_D matrix. 
  data->AEM_D = Eigen::MatrixXd::Zero(21,21);
  data->AEM_D(0,0) = 0.5*As[0]; 
  data->AEM_D(0,1) = 0.5*As[1]; 
  data->AEM_D(0,2) = 0.5*As[2]; 
  data->AEM_D(0,6) = 0.5*As[1]; 
  data->AEM_D(0,7) = 0.4472135954999579*As[4]+0.5*As[0]; 
  data->AEM_D(0,8) = 0.5*As[3]; 
  data->AEM_D(0,12) = 0.5*As[2]; 
  data->AEM_D(0,13) = 0.5*As[3]; 
  data->AEM_D(0,14) = 0.4472135954999579*As[5]+0.5*As[0]; 
  data->AEM_D(1,0) = 0.5*As[0]; 
  data->AEM_D(1,7) = 0.5*As[0]; 
  data->AEM_D(1,14) = 0.5*As[0]; 
  data->AEM_D(1,15) = 0.5*As[3]; 
  data->AEM_D(1,16) = 0.5*As[2]; 
  data->AEM_D(1,17) = 0.5*As[1]; 
  data->AEM_D(2,3) = 0.5*As[1]; 
  data->AEM_D(2,9) = 0.5*As[2]; 
  data->AEM_D(2,16) = 0.5*As[1]; 
  data->AEM_D(3,1) = 0.5*As[2]; 
  data->AEM_D(3,14) = 0.5*As[1]; 
  data->AEM_D(3,20) = 0.5*As[2]; 
  data->AEM_D(4,12) = 0.5*As[4]; 
  data->AEM_D(4,13) = 0.4472135954999579*As[1]; 
  data->AEM_D(4,18) = 0.5*As[5]; 
  data->AEM_D(4,20) = 0.4472135954999579*As[2]; 
 
  // Fill BEV_D. 
  data->BEV_D << Bs[0],Bs[1],Bs[2],Bs[3],Bs[4],Bs[5],Bs[6],Bs[7],Bs[8],Bs[9],Bs[10],Bs[11],Bs[12],Bs[13],Bs[14],Bs[15],Bs[16],Bs[17],Bs[18],Bs[19],Bs[20]; 
 
  // Solve the system of equations. 
  data->u_D = data->AEM_D.colPivHouseholderQr().solve(data->BEV_D); 
 
  // Copy data from Eigen vector. 
  Eigen::Map<VectorXd>(out,21,1) = data->u_D; 
 
} 
 
