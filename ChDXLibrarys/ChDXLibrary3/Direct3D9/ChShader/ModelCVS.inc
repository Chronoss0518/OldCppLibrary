#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 10.1
//
// Parameters:
//
//   struct
//   {
//       row_major float4x4 ViewMat;
//       row_major float4x4 ProMat;
//
//   } Mats;
//   
//   row_major float4x4 ModelMat;
//
//
// Registers:
//
//   Name         Reg   Size
//   ------------ ----- ----
//   Mats         c0       8
//   ModelMat     c8       4
//

    vs_3_0
    dcl_position v0  // Pos<0,1,2,3>
    dcl_position o0
    dcl_texcoord o1.xyz

#line 37 "G:\Desktop\ShaderTest2\Shaders\D3D9\ModelShader\MVContourShader.hlsl"
    mul r0, c8, v0.x
    mul r1, c9, v0.y
    add r0, r0, r1
    mul r1, c10, v0.z
    add r0, r0, r1
    mul r1, c11, v0.w
    add r0, r0, r1  // ::Out<0,1,2,3>

#line 45
    mul r1, r0.x, c0
    mul r2, r0.y, c1
    add r1, r1, r2
    mul r2, r0.z, c2
    add r1, r1, r2
    mul r0, r0.w, c3
    add r0, r0, r1  // ::Out<0,1,2,3>
    mul r1, r0.x, c4
    mul r2, r0.y, c5
    add r1, r1, r2
    mul r2, r0.z, c6
    add r1, r1, r2
    mul r0, r0.w, c7
    add r0, r0, r1  // ::Out<0,1,2,3>
    mov r0.xyz, r0  // ::Out<4,5,6>
    mov o0, r0  // ::main<0,1,2,3>
    mov o1.xyz, r0  // ::main<4,5,6>

// approximately 24 instruction slots used
#endif

const BYTE ModelCVS[] =
{
      0,   3, 254, 255, 254, 255, 
    156,   0,  68,  66,  85,  71, 
     40,   0,   0,   0,  68,   2, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0, 112,   0, 
      0,   0,  27,   0,   0,   0, 
    116,   0,   0,   0,   3,   0, 
      0,   0,   8,   2,   0,   0, 
    204,   1,   0,   0,  71,  58, 
     92,  68, 101, 115, 107, 116, 
    111, 112,  92,  83, 104,  97, 
    100, 101, 114,  84, 101, 115, 
    116,  50,  92,  83, 104,  97, 
    100, 101, 114, 115,  92,  68, 
     51,  68,  57,  92,  77, 111, 
    100, 101, 108,  83, 104,  97, 
    100, 101, 114,  92,  77,  86, 
     67, 111, 110, 116, 111, 117, 
    114,  83, 104,  97, 100, 101, 
    114,  46, 104, 108, 115, 108, 
      0, 171, 171, 171,  40,   0, 
      0,   0,   0,   0, 255, 255, 
     88,   3,   0,   0,   0,   0, 
    255, 255, 100,   3,   0,   0, 
      0,   0, 255, 255, 112,   3, 
      0,   0,  37,   0,   0,   0, 
    124,   3,   0,   0,  37,   0, 
      0,   0, 140,   3,   0,   0, 
     37,   0,   0,   0, 156,   3, 
      0,   0,  37,   0,   0,   0, 
    172,   3,   0,   0,  37,   0, 
      0,   0, 188,   3,   0,   0, 
     37,   0,   0,   0, 204,   3, 
      0,   0,  37,   0,   0,   0, 
    220,   3,   0,   0,  45,   0, 
      0,   0, 236,   3,   0,   0, 
     45,   0,   0,   0, 252,   3, 
      0,   0,  45,   0,   0,   0, 
     12,   4,   0,   0,  45,   0, 
      0,   0,  28,   4,   0,   0, 
     45,   0,   0,   0,  44,   4, 
      0,   0,  45,   0,   0,   0, 
     60,   4,   0,   0,  45,   0, 
      0,   0,  76,   4,   0,   0, 
     47,   0,   0,   0,  92,   4, 
      0,   0,  47,   0,   0,   0, 
    108,   4,   0,   0,  47,   0, 
      0,   0, 124,   4,   0,   0, 
     47,   0,   0,   0, 140,   4, 
      0,   0,  47,   0,   0,   0, 
    156,   4,   0,   0,  47,   0, 
      0,   0, 172,   4,   0,   0, 
     47,   0,   0,   0, 188,   4, 
      0,   0,  49,   0,   0,   0, 
    204,   4,   0,   0,  51,   0, 
      0,   0, 216,   4,   0,   0, 
     51,   0,   0,   0, 228,   4, 
      0,   0,  79, 117, 116,   0, 
     80, 111, 115,   0,   1,   0, 
      3,   0,   1,   0,   4,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,  80, 114, 111,  80, 
    111, 115,   0, 171,   1,   0, 
      3,   0,   1,   0,   3,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,  80,   1,   0,   0, 
     84,   1,   0,   0, 100,   1, 
      0,   0, 108,   1,   0,   0, 
      5,   0,   0,   0,   1,   0, 
      7,   0,   1,   0,   2,   0, 
    124,   1,   0,   0,   9,   0, 
      0,   0,   0,   0,   1,   0, 
      2,   0,   3,   0,  16,   0, 
      0,   0,   0,   0,   1,   0, 
      2,   0,   3,   0,  23,   0, 
      0,   0,   0,   0,   1,   0, 
      2,   0,   3,   0,  24,   0, 
      0,   0,   4,   0,   5,   0, 
      6,   0, 255, 255, 109,  97, 
    105, 110,   0, 171, 171, 171, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   2,   0,   3,   0, 
      5,   0,   0,   0,   1,   0, 
      7,   0,   1,   0,   2,   0, 
    124,   1,   0,   0,  25,   0, 
      0,   0,   0,   0,   1,   0, 
      2,   0,   3,   0,  26,   0, 
      0,   0,   4,   0,   5,   0, 
      6,   0, 255, 255,   0,   0, 
      0,   0,  76,   1,   0,   0, 
    140,   1,   0,   0,   4,   0, 
      0,   0, 156,   1,   0,   0, 
    204,   1,   0,   0,  80,   1, 
      0,   0,  84,   1,   0,   0, 
      1,   0,   0,   0, 212,   1, 
      0,   0,   0,   0,   0,   0, 
    204,   1,   0,   0, 224,   1, 
      0,   0,   2,   0,   0,   0, 
    240,   1,   0,   0,  77, 105, 
     99, 114, 111, 115, 111, 102, 
    116,  32,  40,  82,  41,  32, 
     72,  76,  83,  76,  32,  83, 
    104,  97, 100, 101, 114,  32, 
     67, 111, 109, 112, 105, 108, 
    101, 114,  32,  49,  48,  46, 
     49,   0, 254, 255,  55,   0, 
     67,  84,  65,  66,  28,   0, 
      0,   0, 175,   0,   0,   0, 
      0,   3, 254, 255,   2,   0, 
      0,   0,  28,   0,   0,   0, 
      5,   1,   0,   0, 168,   0, 
      0,   0,  68,   0,   0,   0, 
      2,   0,   0,   0,   8,   0, 
      0,   0, 124,   0,   0,   0, 
      0,   0,   0,   0, 140,   0, 
      0,   0,   2,   0,   8,   0, 
      4,   0,   0,   0, 152,   0, 
      0,   0,   0,   0,   0,   0, 
     77,  97, 116, 115,   0,  86, 
    105, 101, 119,  77,  97, 116, 
      0, 171, 171, 171,   2,   0, 
      3,   0,   4,   0,   4,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,  80, 114, 111,  77, 
     97, 116,   0, 171,  73,   0, 
      0,   0,  84,   0,   0,   0, 
    100,   0,   0,   0,  84,   0, 
      0,   0,   5,   0,   0,   0, 
      1,   0,  32,   0,   1,   0, 
      2,   0, 108,   0,   0,   0, 
     77, 111, 100, 101, 108,  77, 
     97, 116,   0, 171, 171, 171, 
      2,   0,   3,   0,   4,   0, 
      4,   0,   1,   0,   0,   0, 
      0,   0,   0,   0, 118, 115, 
     95,  51,  95,  48,   0,  77, 
    105,  99, 114, 111, 115, 111, 
    102, 116,  32,  40,  82,  41, 
     32,  72,  76,  83,  76,  32, 
     83, 104,  97, 100, 101, 114, 
     32,  67, 111, 109, 112, 105, 
    108, 101, 114,  32,  49,  48, 
     46,  49,   0, 171,  31,   0, 
      0,   2,   0,   0,   0, 128, 
      0,   0,  15, 144,  31,   0, 
      0,   2,   0,   0,   0, 128, 
      0,   0,  15, 224,  31,   0, 
      0,   2,   5,   0,   0, 128, 
      1,   0,   7, 224,   5,   0, 
      0,   3,   0,   0,  15, 128, 
      8,   0, 228, 160,   0,   0, 
      0, 144,   5,   0,   0,   3, 
      1,   0,  15, 128,   9,   0, 
    228, 160,   0,   0,  85, 144, 
      2,   0,   0,   3,   0,   0, 
     15, 128,   0,   0, 228, 128, 
      1,   0, 228, 128,   5,   0, 
      0,   3,   1,   0,  15, 128, 
     10,   0, 228, 160,   0,   0, 
    170, 144,   2,   0,   0,   3, 
      0,   0,  15, 128,   0,   0, 
    228, 128,   1,   0, 228, 128, 
      5,   0,   0,   3,   1,   0, 
     15, 128,  11,   0, 228, 160, 
      0,   0, 255, 144,   2,   0, 
      0,   3,   0,   0,  15, 128, 
      0,   0, 228, 128,   1,   0, 
    228, 128,   5,   0,   0,   3, 
      1,   0,  15, 128,   0,   0, 
      0, 128,   0,   0, 228, 160, 
      5,   0,   0,   3,   2,   0, 
     15, 128,   0,   0,  85, 128, 
      1,   0, 228, 160,   2,   0, 
      0,   3,   1,   0,  15, 128, 
      1,   0, 228, 128,   2,   0, 
    228, 128,   5,   0,   0,   3, 
      2,   0,  15, 128,   0,   0, 
    170, 128,   2,   0, 228, 160, 
      2,   0,   0,   3,   1,   0, 
     15, 128,   1,   0, 228, 128, 
      2,   0, 228, 128,   5,   0, 
      0,   3,   0,   0,  15, 128, 
      0,   0, 255, 128,   3,   0, 
    228, 160,   2,   0,   0,   3, 
      0,   0,  15, 128,   0,   0, 
    228, 128,   1,   0, 228, 128, 
      5,   0,   0,   3,   1,   0, 
     15, 128,   0,   0,   0, 128, 
      4,   0, 228, 160,   5,   0, 
      0,   3,   2,   0,  15, 128, 
      0,   0,  85, 128,   5,   0, 
    228, 160,   2,   0,   0,   3, 
      1,   0,  15, 128,   1,   0, 
    228, 128,   2,   0, 228, 128, 
      5,   0,   0,   3,   2,   0, 
     15, 128,   0,   0, 170, 128, 
      6,   0, 228, 160,   2,   0, 
      0,   3,   1,   0,  15, 128, 
      1,   0, 228, 128,   2,   0, 
    228, 128,   5,   0,   0,   3, 
      0,   0,  15, 128,   0,   0, 
    255, 128,   7,   0, 228, 160, 
      2,   0,   0,   3,   0,   0, 
     15, 128,   0,   0, 228, 128, 
      1,   0, 228, 128,   1,   0, 
      0,   2,   0,   0,   7, 128, 
      0,   0, 228, 128,   1,   0, 
      0,   2,   0,   0,  15, 224, 
      0,   0, 228, 128,   1,   0, 
      0,   2,   1,   0,   7, 224, 
      0,   0, 228, 128, 255, 255, 
      0,   0
};
