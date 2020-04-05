#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 10.1
//
// Parameters:
//
//   row_major float4x4 ModelMat;
//   float4 WindSize;
//
//
// Registers:
//
//   Name         Reg   Size
//   ------------ ----- ----
//   ModelMat     c0       4
//   WindSize     c4       1
//

    vs_3_0
    def c5, 2, -2, 0, -1
    dcl_position v0  // pos<0,1,2>
    dcl_color v1  // color<0,1,2,3>
    dcl_texcoord v2  // uv<0,1>
    dcl_position o0
    dcl_color o1
    dcl_texcoord o2.xy

#line 30 "G:\Desktop\ShaderTest2\Shaders\D3D9\TextureShader\STVShader.hlsl"
    mov r0.xyz, v0  // ::Out<0,1,2>

#line 35
    rcp r0.w, c4.x
    mul r1.x, r0.w, c5.x  // ::SpProMat<0>
    rcp r0.w, c4.y
    mul r2.y, r0.w, c5.y  // ::SpProMat<5>
    mov r1.yzw, c5.xzzw  // ::SpProMat<4,8,12>
    mov r2.xzw, c5_abs.zyzw  // ::SpProMat<1,9,13>

#line 41
    mul r3, r0.x, c0
    mul r4, r0.y, c1
    add r3, r3, r4
    mul r0, r0.z, c2
    add r0, r0, r3
    mov r3.w, c5.w
    mul r3, -r3.w, c3
    add r0, r0, r3  // ::Out<0,1,2,3>
    dp4 r1.x, r0, r1  // ::Out<0>
    dp4 r1.y, r0, r2  // ::Out<1>
    dp4 r1.z, r0.xywz, c5_abs.zzzw  // ::Out<2>
    dp4 r1.w, r0, c5_abs.zzzw  // ::Out<3>
    mov r0, v1  // ::Out<4,5,6,7>

#line 48
    mov r2.xy, v2  // ::Out<8,9>

#line 51
    mov o0, r1  // ::main<0,1,2,3>
    mov o1, r0  // ::main<4,5,6,7>
    mov o2.xy, r2  // ::main<8,9>

// approximately 24 instruction slots used
#endif

const BYTE SpTexVS[] =
{
      0,   3, 254, 255, 254, 255, 
    228,   0,  68,  66,  85,  71, 
     40,   0,   0,   0, 100,   3, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0, 108,   0, 
      0,   0,  31,   0,   0,   0, 
    112,   0,   0,   0,   6,   0, 
      0,   0, 236,   2,   0,   0, 
    112,   2,   0,   0,  71,  58, 
     92,  68, 101, 115, 107, 116, 
    111, 112,  92,  83, 104,  97, 
    100, 101, 114,  84, 101, 115, 
    116,  50,  92,  83, 104,  97, 
    100, 101, 114, 115,  92,  68, 
     51,  68,  57,  92,  84, 101, 
    120, 116, 117, 114, 101,  83, 
    104,  97, 100, 101, 114,  92, 
     83,  84,  86,  83, 104,  97, 
    100, 101, 114,  46, 104, 108, 
    115, 108,   0, 171, 171, 171, 
     40,   0,   0,   0,   0,   0, 
    255, 255,  92,   4,   0,   0, 
      0,   0, 255, 255, 116,   4, 
      0,   0,   0,   0, 255, 255, 
    128,   4,   0,   0,   0,   0, 
    255, 255, 140,   4,   0,   0, 
      0,   0, 255, 255, 152,   4, 
      0,   0,   0,   0, 255, 255, 
    164,   4,   0,   0,   0,   0, 
    255, 255, 176,   4,   0,   0, 
     30,   0,   0,   0, 188,   4, 
      0,   0,  35,   0,   0,   0, 
    200,   4,   0,   0,  35,   0, 
      0,   0, 212,   4,   0,   0, 
     36,   0,   0,   0, 228,   4, 
      0,   0,  36,   0,   0,   0, 
    240,   4,   0,   0,  34,   0, 
      0,   0,   0,   5,   0,   0, 
     34,   0,   0,   0,  12,   5, 
      0,   0,  41,   0,   0,   0, 
     24,   5,   0,   0,  41,   0, 
      0,   0,  40,   5,   0,   0, 
     41,   0,   0,   0,  56,   5, 
      0,   0,  41,   0,   0,   0, 
     72,   5,   0,   0,  41,   0, 
      0,   0,  88,   5,   0,   0, 
     41,   0,   0,   0, 104,   5, 
      0,   0,  41,   0,   0,   0, 
    116,   5,   0,   0,  41,   0, 
      0,   0, 132,   5,   0,   0, 
     43,   0,   0,   0, 148,   5, 
      0,   0,  43,   0,   0,   0, 
    164,   5,   0,   0,  43,   0, 
      0,   0, 180,   5,   0,   0, 
     43,   0,   0,   0, 196,   5, 
      0,   0,  45,   0,   0,   0, 
    212,   5,   0,   0,  48,   0, 
      0,   0, 224,   5,   0,   0, 
     51,   0,   0,   0, 236,   5, 
      0,   0,  51,   0,   0,   0, 
    248,   5,   0,   0,  51,   0, 
      0,   0,   4,   6,   0,   0, 
     79, 117, 116,   0,  80, 111, 
    115,   0,   1,   0,   3,   0, 
      1,   0,   4,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
     67, 111, 108, 111, 114,   0, 
     85,  86,   0, 171, 171, 171, 
      1,   0,   3,   0,   1,   0, 
      2,   0,   1,   0,   0,   0, 
      0,   0,   0,   0, 108,   1, 
      0,   0, 112,   1,   0,   0, 
    128,   1,   0,   0, 112,   1, 
      0,   0, 134,   1,   0,   0, 
    140,   1,   0,   0,   5,   0, 
      0,   0,   1,   0,  10,   0, 
      1,   0,   3,   0, 156,   1, 
      0,   0,   7,   0,   0,   0, 
      0,   0,   1,   0,   2,   0, 
    255, 255,  21,   0,   0,   0, 
      0,   0,   1,   0,   2,   0, 
      3,   0,  22,   0,   0,   0, 
      0,   0, 255, 255, 255, 255, 
    255, 255,  23,   0,   0,   0, 
    255, 255,   1,   0, 255, 255, 
    255, 255,  24,   0,   0,   0, 
    255, 255, 255, 255,   2,   0, 
    255, 255,  25,   0,   0,   0, 
    255, 255, 255, 255, 255, 255, 
      3,   0,  26,   0,   0,   0, 
      4,   0,   5,   0,   6,   0, 
      7,   0,  27,   0,   0,   0, 
      8,   0,   9,   0, 255, 255, 
    255, 255,  83, 112,  80, 114, 
    111,  77,  97, 116,   0, 171, 
    171, 171,   3,   0,   3,   0, 
      4,   0,   4,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      9,   0,   0,   0,   0,   0, 
    255, 255, 255, 255, 255, 255, 
     11,   0,   0,   0, 255, 255, 
      5,   0, 255, 255, 255, 255, 
     12,   0,   0,   0, 255, 255, 
      4,   0,   8,   0,  12,   0, 
     13,   0,   0,   0,   1,   0, 
    255, 255,   9,   0,  13,   0, 
    109,  97, 105, 110,   0,  99, 
    111, 108, 111, 114,   0, 171, 
      2,   0,   0,   0,   0,   0, 
      1,   0,   2,   0,   3,   0, 
      5,   0,   0,   0,   1,   0, 
     10,   0,   1,   0,   3,   0, 
    156,   1,   0,   0,  28,   0, 
      0,   0,   0,   0,   1,   0, 
      2,   0,   3,   0,  29,   0, 
      0,   0,   4,   0,   5,   0, 
      6,   0,   7,   0,  30,   0, 
      0,   0,   8,   0,   9,   0, 
    255, 255, 255, 255, 112, 111, 
    115,   0,   1,   0,   3,   0, 
      1,   0,   3,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      1,   0,   2,   0, 255, 255, 
    117, 118,   0, 171,   3,   0, 
      0,   0,   0,   0,   1,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0, 104,   1,   0,   0, 
    180,   1,   0,   0,   8,   0, 
      0,   0, 196,   1,   0,   0, 
      0,   0,   0,   0,  36,   2, 
      0,   0,  48,   2,   0,   0, 
      4,   0,   0,   0,  64,   2, 
      0,   0, 112,   2,   0,   0, 
    117,   2,   0,   0, 112,   1, 
      0,   0,   1,   0,   0,   0, 
    124,   2,   0,   0,   0,   0, 
      0,   0, 112,   2,   0,   0, 
    136,   2,   0,   0,   3,   0, 
      0,   0, 152,   2,   0,   0, 
    112,   2,   0,   0, 188,   2, 
      0,   0, 192,   2,   0,   0, 
      1,   0,   0,   0, 208,   2, 
      0,   0, 112,   2,   0,   0, 
    220,   2,   0,   0, 140,   1, 
      0,   0,   1,   0,   0,   0, 
    224,   2,   0,   0,  77, 105, 
     99, 114, 111, 115, 111, 102, 
    116,  32,  40,  82,  41,  32, 
     72,  76,  83,  76,  32,  83, 
    104,  97, 100, 101, 114,  32, 
     67, 111, 109, 112, 105, 108, 
    101, 114,  32,  49,  48,  46, 
     49,   0, 254, 255,  48,   0, 
     67,  84,  65,  66,  28,   0, 
      0,   0, 147,   0,   0,   0, 
      0,   3, 254, 255,   2,   0, 
      0,   0,  28,   0,   0,   0, 
      5,   1,   0,   0, 140,   0, 
      0,   0,  68,   0,   0,   0, 
      2,   0,   0,   0,   4,   0, 
      0,   0,  80,   0,   0,   0, 
      0,   0,   0,   0,  96,   0, 
      0,   0,   2,   0,   4,   0, 
      1,   0,   0,   0, 108,   0, 
      0,   0, 124,   0,   0,   0, 
     77, 111, 100, 101, 108,  77, 
     97, 116,   0, 171, 171, 171, 
      2,   0,   3,   0,   4,   0, 
      4,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,  87, 105, 
    110, 100,  83, 105, 122, 101, 
      0, 171, 171, 171,   1,   0, 
      3,   0,   1,   0,   4,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 160,  68, 
      0,   0,  52,  68,   0,   0, 
      0,   0,   0,   0,   0,   0, 
    118, 115,  95,  51,  95,  48, 
      0,  77, 105,  99, 114, 111, 
    115, 111, 102, 116,  32,  40, 
     82,  41,  32,  72,  76,  83, 
     76,  32,  83, 104,  97, 100, 
    101, 114,  32,  67, 111, 109, 
    112, 105, 108, 101, 114,  32, 
     49,  48,  46,  49,   0, 171, 
     81,   0,   0,   5,   5,   0, 
     15, 160,   0,   0,   0,  64, 
      0,   0,   0, 192,   0,   0, 
      0,   0,   0,   0, 128, 191, 
     31,   0,   0,   2,   0,   0, 
      0, 128,   0,   0,  15, 144, 
     31,   0,   0,   2,  10,   0, 
      0, 128,   1,   0,  15, 144, 
     31,   0,   0,   2,   5,   0, 
      0, 128,   2,   0,  15, 144, 
     31,   0,   0,   2,   0,   0, 
      0, 128,   0,   0,  15, 224, 
     31,   0,   0,   2,  10,   0, 
      0, 128,   1,   0,  15, 224, 
     31,   0,   0,   2,   5,   0, 
      0, 128,   2,   0,   3, 224, 
      1,   0,   0,   2,   0,   0, 
      7, 128,   0,   0, 228, 144, 
      6,   0,   0,   2,   0,   0, 
      8, 128,   4,   0,   0, 160, 
      5,   0,   0,   3,   1,   0, 
      1, 128,   0,   0, 255, 128, 
      5,   0,   0, 160,   6,   0, 
      0,   2,   0,   0,   8, 128, 
      4,   0,  85, 160,   5,   0, 
      0,   3,   2,   0,   2, 128, 
      0,   0, 255, 128,   5,   0, 
     85, 160,   1,   0,   0,   2, 
      1,   0,  14, 128,   5,   0, 
    232, 160,   1,   0,   0,   2, 
      2,   0,  13, 128,   5,   0, 
    230, 171,   5,   0,   0,   3, 
      3,   0,  15, 128,   0,   0, 
      0, 128,   0,   0, 228, 160, 
      5,   0,   0,   3,   4,   0, 
     15, 128,   0,   0,  85, 128, 
      1,   0, 228, 160,   2,   0, 
      0,   3,   3,   0,  15, 128, 
      3,   0, 228, 128,   4,   0, 
    228, 128,   5,   0,   0,   3, 
      0,   0,  15, 128,   0,   0, 
    170, 128,   2,   0, 228, 160, 
      2,   0,   0,   3,   0,   0, 
     15, 128,   0,   0, 228, 128, 
      3,   0, 228, 128,   1,   0, 
      0,   2,   3,   0,   8, 128, 
      5,   0, 255, 160,   5,   0, 
      0,   3,   3,   0,  15, 128, 
      3,   0, 255, 129,   3,   0, 
    228, 160,   2,   0,   0,   3, 
      0,   0,  15, 128,   0,   0, 
    228, 128,   3,   0, 228, 128, 
      9,   0,   0,   3,   1,   0, 
      1, 128,   0,   0, 228, 128, 
      1,   0, 228, 128,   9,   0, 
      0,   3,   1,   0,   2, 128, 
      0,   0, 228, 128,   2,   0, 
    228, 128,   9,   0,   0,   3, 
      1,   0,   4, 128,   0,   0, 
    180, 128,   5,   0, 234, 171, 
      9,   0,   0,   3,   1,   0, 
      8, 128,   0,   0, 228, 128, 
      5,   0, 234, 171,   1,   0, 
      0,   2,   0,   0,  15, 128, 
      1,   0, 228, 144,   1,   0, 
      0,   2,   2,   0,   3, 128, 
      2,   0, 228, 144,   1,   0, 
      0,   2,   0,   0,  15, 224, 
      1,   0, 228, 128,   1,   0, 
      0,   2,   1,   0,  15, 224, 
      0,   0, 228, 128,   1,   0, 
      0,   2,   2,   0,   3, 224, 
      2,   0, 228, 128, 255, 255, 
      0,   0
};