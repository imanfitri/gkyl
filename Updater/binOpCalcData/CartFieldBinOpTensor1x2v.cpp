#include <math.h> 
#include <CartFieldBinOpModDecl.h> 
 
using namespace Eigen; 
 
void CartFieldBinOpMultiply1x2vTensor_P1(binOpData_t* data, const double *A, const double *B, const short int Ncomp, const short int eqNcomp, double *out) 
{ 
  // A:       scalar/vector field in configuration space. 
  // B:       scalar field in phase space. 
  // Ncomp:   number of components of B (should =1 here). 
  // eqNcomp: =1 if A:numComponents=B:numComponents, =0 else (should=1 here). 
  // out:     output field A*B (same number of components as B). 
 
  double tmp[8]; 
  tmp[0] = 0.7071067811865475*A[1]*B[1]+0.7071067811865475*A[0]*B[0]; 
  tmp[1] = 0.7071067811865475*A[0]*B[1]+0.7071067811865475*B[0]*A[1]; 
  tmp[2] = 0.7071067811865475*A[1]*B[4]+0.7071067811865475*A[0]*B[2]; 
  tmp[3] = 0.7071067811865475*A[1]*B[5]+0.7071067811865475*A[0]*B[3]; 
  tmp[4] = 0.7071067811865475*A[0]*B[4]+0.7071067811865475*A[1]*B[2]; 
  tmp[5] = 0.7071067811865475*A[0]*B[5]+0.7071067811865475*A[1]*B[3]; 
  tmp[6] = 0.7071067811865475*A[1]*B[7]+0.7071067811865475*A[0]*B[6]; 
  tmp[7] = 0.7071067811865475*A[0]*B[7]+0.7071067811865475*A[1]*B[6]; 
 
  // This tmp allows for in-place multiplication. 
  for (unsigned short int i=0; i<8; i++) 
  { 
    out[i] = tmp[i]; 
  } 
 
} 
 
void CartFieldBinOpMultiply1x2vTensor_P2(binOpData_t* data, const double *A, const double *B, const short int Ncomp, const short int eqNcomp, double *out) 
{ 
  // A:       scalar/vector field in configuration space. 
  // B:       scalar field in phase space. 
  // Ncomp:   number of components of B (should =1 here). 
  // eqNcomp: =1 if A:numComponents=B:numComponents, =0 else (should=1 here). 
  // out:     output field A*B (same number of components as B). 
 
  double tmp[27]; 
  tmp[0] = 0.7071067811865475*A[2]*B[7]+0.7071067811865475*A[1]*B[1]+0.7071067811865475*A[0]*B[0]; 
  tmp[1] = 0.6324555320336759*A[1]*B[7]+0.6324555320336759*B[1]*A[2]+0.7071067811865475*A[0]*B[1]+0.7071067811865475*B[0]*A[1]; 
  tmp[2] = 0.7071067811865475*A[2]*B[11]+0.7071067811865475*A[1]*B[4]+0.7071067811865475*A[0]*B[2]; 
  tmp[3] = 0.7071067811865475*A[2]*B[13]+0.7071067811865475*A[1]*B[5]+0.7071067811865475*A[0]*B[3]; 
  tmp[4] = 0.632455532033676*A[1]*B[11]+0.6324555320336759*A[2]*B[4]+0.7071067811865475*A[0]*B[4]+0.7071067811865475*A[1]*B[2]; 
  tmp[5] = 0.632455532033676*A[1]*B[13]+0.6324555320336759*A[2]*B[5]+0.7071067811865475*A[0]*B[5]+0.7071067811865475*A[1]*B[3]; 
  tmp[6] = 0.7071067811865475*A[2]*B[17]+0.7071067811865475*A[1]*B[10]+0.7071067811865475*A[0]*B[6]; 
  tmp[7] = 0.4517539514526256*A[2]*B[7]+0.7071067811865475*A[0]*B[7]+0.7071067811865475*B[0]*A[2]+0.6324555320336759*A[1]*B[1]; 
  tmp[8] = 0.7071067811865475*A[2]*B[20]+0.7071067811865475*A[1]*B[12]+0.7071067811865475*A[0]*B[8]; 
  tmp[9] = 0.7071067811865475*A[2]*B[21]+0.7071067811865475*A[1]*B[15]+0.7071067811865475*A[0]*B[9]; 
  tmp[10] = 0.6324555320336759*A[1]*B[17]+0.6324555320336759*A[2]*B[10]+0.7071067811865475*A[0]*B[10]+0.7071067811865475*A[1]*B[6]; 
  tmp[11] = 0.4517539514526256*A[2]*B[11]+0.7071067811865475*A[0]*B[11]+0.632455532033676*A[1]*B[4]+0.7071067811865475*A[2]*B[2]; 
  tmp[12] = 0.632455532033676*A[1]*B[20]+0.6324555320336759*A[2]*B[12]+0.7071067811865475*A[0]*B[12]+0.7071067811865475*A[1]*B[8]; 
  tmp[13] = 0.4517539514526256*A[2]*B[13]+0.7071067811865475*A[0]*B[13]+0.632455532033676*A[1]*B[5]+0.7071067811865475*A[2]*B[3]; 
  tmp[14] = 0.7071067811865475*A[2]*B[23]+0.7071067811865475*A[1]*B[18]+0.7071067811865475*A[0]*B[14]; 
  tmp[15] = 0.632455532033676*A[1]*B[21]+0.6324555320336759*A[2]*B[15]+0.7071067811865475*A[0]*B[15]+0.7071067811865475*A[1]*B[9]; 
  tmp[16] = 0.7071067811865475*A[2]*B[24]+0.7071067811865475*A[1]*B[19]+0.7071067811865475*A[0]*B[16]; 
  tmp[17] = 0.4517539514526256*A[2]*B[17]+0.7071067811865475*A[0]*B[17]+0.6324555320336759*A[1]*B[10]+0.7071067811865475*A[2]*B[6]; 
  tmp[18] = 0.6324555320336759*A[1]*B[23]+0.6324555320336759*A[2]*B[18]+0.7071067811865475*A[0]*B[18]+0.7071067811865475*A[1]*B[14]; 
  tmp[19] = 0.6324555320336759*A[1]*B[24]+0.6324555320336759*A[2]*B[19]+0.7071067811865475*A[0]*B[19]+0.7071067811865475*A[1]*B[16]; 
  tmp[20] = 0.4517539514526256*A[2]*B[20]+0.7071067811865475*A[0]*B[20]+0.632455532033676*A[1]*B[12]+0.7071067811865475*A[2]*B[8]; 
  tmp[21] = 0.4517539514526256*A[2]*B[21]+0.7071067811865475*A[0]*B[21]+0.632455532033676*A[1]*B[15]+0.7071067811865475*A[2]*B[9]; 
  tmp[22] = 0.7071067811865475*A[2]*B[26]+0.7071067811865475*A[1]*B[25]+0.7071067811865475*A[0]*B[22]; 
  tmp[23] = 0.4517539514526256*A[2]*B[23]+0.7071067811865475*A[0]*B[23]+0.6324555320336759*A[1]*B[18]+0.7071067811865475*A[2]*B[14]; 
  tmp[24] = 0.4517539514526256*A[2]*B[24]+0.7071067811865475*A[0]*B[24]+0.6324555320336759*A[1]*B[19]+0.7071067811865475*A[2]*B[16]; 
  tmp[25] = 0.6324555320336759*A[1]*B[26]+0.6324555320336759*A[2]*B[25]+0.7071067811865475*A[0]*B[25]+0.7071067811865475*A[1]*B[22]; 
  tmp[26] = 0.4517539514526256*A[2]*B[26]+0.7071067811865475*A[0]*B[26]+0.6324555320336759*A[1]*B[25]+0.7071067811865475*A[2]*B[22]; 
 
  // This tmp allows for in-place multiplication. 
  for (unsigned short int i=0; i<27; i++) 
  { 
    out[i] = tmp[i]; 
  } 
 
} 
 
void CartFieldBinOpDivide1x2vTensor_P1(binOpData_t* data, const double *A, const double *B, const short int Ncomp, const short int eqNcomp, double *out) 
{ 
  // A:       configuration space denominator field (must be a scalar field). 
  // B:       phase space numerator field (must be a scalar field). 
  // Ncomp:   number of components of B (=1 here). 
  // eqNcomp: =1 if A:numComponents=B:numComponents, =0 else (=1 here). 
  // out:     output field (same number of components as B). 
 
  // If a corner value is below zero, use cell average A.
  bool avgA = false;
  if (0.7071067811865475*A[0]-1.224744871391589*A[1] < 0) { 
    avgA = true;
  }
  if (1.224744871391589*A[1]+0.7071067811865475*A[0] < 0) { 
    avgA = true;
  }
 
  double As[2]; 
  double Bs[8]; 
  if (avgA) { 
    As[0] = A[0]; 
    As[1] = 0.0; 
    Bs[0] = B[0]; 
    Bs[1] = 0.0; 
    Bs[2] = B[2]; 
    Bs[3] = B[3]; 
    Bs[4] = 0.0; 
    Bs[5] = 0.0; 
    Bs[6] = B[6]; 
    Bs[7] = 0.0; 
  } else { 
    As[0] = A[0]; 
    As[1] = A[1]; 
    Bs[0] = B[0]; 
    Bs[1] = B[1]; 
    Bs[2] = B[2]; 
    Bs[3] = B[3]; 
    Bs[4] = B[4]; 
    Bs[5] = B[5]; 
    Bs[6] = B[6]; 
    Bs[7] = B[7]; 
  } 
 
  // Fill AEM_D matrix. 
  data->AEM_D = Eigen::MatrixXd::Zero(8,8);
  data->AEM_D(0,0) = 0.7071067811865475*As[0]; 
  data->AEM_D(0,1) = 0.7071067811865475*As[1]; 
  data->AEM_D(0,2) = 0.7071067811865475*As[1]; 
  data->AEM_D(0,3) = 0.7071067811865475*As[0]; 
 
  // Fill BEV_D. 
  data->BEV_D << Bs[0],Bs[1],Bs[2],Bs[3],Bs[4],Bs[5],Bs[6],Bs[7]; 
 
  // Solve the system of equations. 
  data->u_D = data->AEM_D.colPivHouseholderQr().solve(data->BEV_D); 
 
  // Copy data from Eigen vector. 
  Eigen::Map<VectorXd>(out,8,1) = data->u_D; 
 
} 
 
void CartFieldBinOpDivide1x2vTensor_P2(binOpData_t* data, const double *A, const double *B, const short int Ncomp, const short int eqNcomp, double *out) 
{ 
  // A:       configuration space denominator field (must be a scalar field). 
  // B:       phase space numerator field (must be a scalar field). 
  // Ncomp:   number of components of B (=1 here). 
  // eqNcomp: =1 if A:numComponents=B:numComponents, =0 else (=1 here). 
  // out:     output field (same number of components as B). 
 
  // If a corner value is below zero, use cell average A.
  bool avgA = false;
  if (1.58113883008419*A[2]-1.224744871391589*A[1]+0.7071067811865475*A[0] < 0) { 
    avgA = true;
  }
  if (1.58113883008419*A[2]+1.224744871391589*A[1]+0.7071067811865475*A[0] < 0) { 
    avgA = true;
  }
 
  double As[3]; 
  double Bs[27]; 
  if (avgA) { 
    As[0] = A[0]; 
    As[1] = 0.0; 
    As[2] = 0.0; 
    Bs[0] = B[0]; 
    Bs[1] = 0.0; 
    Bs[2] = B[2]; 
    Bs[3] = B[3]; 
    Bs[4] = 0.0; 
    Bs[5] = 0.0; 
    Bs[6] = B[6]; 
    Bs[7] = 0.0; 
    Bs[8] = B[8]; 
    Bs[9] = B[9]; 
    Bs[10] = 0.0; 
    Bs[11] = 0.0; 
    Bs[12] = 0.0; 
    Bs[13] = 0.0; 
    Bs[14] = B[14]; 
    Bs[15] = 0.0; 
    Bs[16] = B[16]; 
    Bs[17] = 0.0; 
    Bs[18] = 0.0; 
    Bs[19] = 0.0; 
    Bs[20] = 0.0; 
    Bs[21] = 0.0; 
    Bs[22] = B[22]; 
    Bs[23] = 0.0; 
    Bs[24] = 0.0; 
    Bs[25] = 0.0; 
    Bs[26] = 0.0; 
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
    Bs[21] = B[21]; 
    Bs[22] = B[22]; 
    Bs[23] = B[23]; 
    Bs[24] = B[24]; 
    Bs[25] = B[25]; 
    Bs[26] = B[26]; 
  } 
 
  // Fill AEM_D matrix. 
  data->AEM_D = Eigen::MatrixXd::Zero(27,27);
  data->AEM_D(0,0) = 0.7071067811865475*As[0]; 
  data->AEM_D(0,1) = 0.7071067811865475*As[1]; 
  data->AEM_D(0,3) = 0.7071067811865475*As[1]; 
  data->AEM_D(0,4) = 0.6324555320336759*As[2]+0.7071067811865475*As[0]; 
  data->AEM_D(0,8) = 0.7071067811865475*As[0]; 
  data->AEM_D(0,14) = 0.7071067811865475*As[1]; 
  data->AEM_D(0,21) = 0.7071067811865475*As[2]; 
  data->AEM_D(0,22) = 0.6324555320336759*As[1]; 
  data->AEM_D(1,8) = 0.7071067811865475*As[2]; 
 
  // Fill BEV_D. 
  data->BEV_D << Bs[0],Bs[1],Bs[2],Bs[3],Bs[4],Bs[5],Bs[6],Bs[7],Bs[8],Bs[9],Bs[10],Bs[11],Bs[12],Bs[13],Bs[14],Bs[15],Bs[16],Bs[17],Bs[18],Bs[19],Bs[20],Bs[21],Bs[22],Bs[23],Bs[24],Bs[25],Bs[26]; 
 
  // Solve the system of equations. 
  data->u_D = data->AEM_D.colPivHouseholderQr().solve(data->BEV_D); 
 
  // Copy data from Eigen vector. 
  Eigen::Map<VectorXd>(out,27,1) = data->u_D; 
 
} 
 
