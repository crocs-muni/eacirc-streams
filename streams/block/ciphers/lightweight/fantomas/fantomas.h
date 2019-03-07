//
// Created by mhajas on 7/7/18.
//

#pragma once

#include <streams/block/ciphers/lightweight/lightweight.h>
#include <streams/block/ciphers/lightweight/common/cipher.h>

#define LBOX_WORD ROM_DATA_WORD
#define READ_LBOX_WORD READ_ROM_DATA_WORD

#define LBOX_INV_WORD ROM_DATA_WORD
#define READ_LBOX_INV_WORD READ_ROM_DATA_WORD

#define SBOX_Inv(x) do {                   \
  uint16_t __t0, __t1, __t2;               \
  /* S5 Inv */                             \
  x[1] ^= x[0];                            \
  x[1] ^= x[2] & x[4];                     \
  x[4] ^= x[1];                            \
  x[0] ^= x[1] & x[3];                     \
  x[2] ^= x[3];                            \
  x[3] ^= x[0] & x[4];                     \
  x[1] ^= x[2];                            \
  x[2] ^= x[0] & x[1];                     \
  /* Truncate-Xor */                       \
  x[5] ^= x[0];                            \
  x[6] ^= x[1];                            \
  x[7] ^= x[2];                            \
  /* S3: 3-bit Keccak Sbox (involution) */ \
  __t0 = x[5]; __t1 = x[6]; __t2 = x[7];   \
  x[5] ^= (~__t1) & __t2;                  \
  x[6] ^= (~__t2) & __t0;                  \
  x[7] ^= (~__t0) & __t1;                  \
  /* Key */                                \
  x[3] = ~x[3];                            \
  x[4] = ~x[4];                            \
  /* Extend-Xor */                         \
  x[0] ^= x[5];                            \
  x[1] ^= x[6];                            \
  x[2] ^= x[7];                            \
  /* S5 Inv */                             \
  x[1] ^= x[0];                            \
  x[1] ^= x[2] & x[4];                     \
  x[4] ^= x[1];                            \
  x[0] ^= x[1] & x[3];                     \
  x[2] ^= x[3];                            \
  x[3] ^= x[0] & x[4];                     \
  x[1] ^= x[2];                            \
  x[2] ^= x[0] & x[1];                     \
} while(0)

#define SBOX(x) do {                       \
  uint16_t __t0, __t1, __t2;               \
  /* S5 */                                 \
  x[2] ^= x[0] & x[1];                     \
  x[1] ^= x[2];                            \
  x[3] ^= x[0] & x[4];                     \
  x[2] ^= x[3];                            \
  x[0] ^= x[1] & x[3];                     \
  x[4] ^= x[1];                            \
  x[1] ^= x[2] & x[4];                     \
  x[1] ^= x[0];                            \
  /* Extend-Xor */                         \
  x[0] ^= x[5];                            \
  x[1] ^= x[6];                            \
  x[2] ^= x[7];                            \
  /* Key */                                \
  x[3] = ~x[3];                            \
  x[4] = ~x[4];                            \
  /* S3: 3-bit Keccak S-box */             \
  __t0 = x[5]; __t1 = x[6]; __t2 = x[7];   \
  x[5] ^= (~__t1) & __t2;                  \
  x[6] ^= (~__t2) & __t0;                  \
  x[7] ^= (~__t0) & __t1;                  \
  /* Truncate-Xor */                       \
  x[5] ^= x[0];                            \
  x[6] ^= x[1];                            \
  x[7] ^= x[2];                            \
  /* S5 */                                 \
  x[2] ^= x[0] & x[1];                     \
  x[1] ^= x[2];                            \
  x[3] ^= x[0] & x[4];                     \
  x[2] ^= x[3];                            \
  x[0] ^= x[1] & x[3];                     \
  x[4] ^= x[1];                            \
  x[1] ^= x[2] & x[4];                     \
  x[1] ^= x[0];                            \
} while(0)

#define FANTOMAS_BLOCK_SIZE 16

#define FANTOMAS_KEY_SIZE 16

#define FANTOMAS_ROUND_KEYS_SIZE 16
#define FANTOMAS_NUMBER_OF_ROUNDS 12

namespace block {

    class fantomas : public lightweight<FANTOMAS_KEY_SIZE, FANTOMAS_BLOCK_SIZE> {

        LBOX_WORD LBox1[256] = {
                0x0000, 0xbfff, 0x6e90, 0xd16f, 0x4137, 0xfec8, 0x2fa7, 0x9058,
                0xd548, 0x6ab7, 0xbbd8, 0x0427, 0x947f, 0x2b80, 0xfaef, 0x4510,
                0x5296, 0xed69, 0x3c06, 0x83f9, 0x13a1, 0xac5e, 0x7d31, 0xc2ce,
                0x87de, 0x3821, 0xe94e, 0x56b1, 0xc6e9, 0x7916, 0xa879, 0x1786,
                0xd183, 0x6e7c, 0xbf13, 0x00ec, 0x90b4, 0x2f4b, 0xfe24, 0x41db,
                0x04cb, 0xbb34, 0x6a5b, 0xd5a4, 0x45fc, 0xfa03, 0x2b6c, 0x9493,
                0x8315, 0x3cea, 0xed85, 0x527a, 0xc222, 0x7ddd, 0xacb2, 0x134d,
                0x565d, 0xe9a2, 0x38cd, 0x8732, 0x176a, 0xa895, 0x79fa, 0xc605,
                0xc2b1, 0x7d4e, 0xac21, 0x13de, 0x8386, 0x3c79, 0xed16, 0x52e9,
                0x17f9, 0xa806, 0x7969, 0xc696, 0x56ce, 0xe931, 0x385e, 0x87a1,
                0x9027, 0x2fd8, 0xfeb7, 0x4148, 0xd110, 0x6eef, 0xbf80, 0x007f,
                0x456f, 0xfa90, 0x2bff, 0x9400, 0x0458, 0xbba7, 0x6ac8, 0xd537,
                0x1332, 0xaccd, 0x7da2, 0xc25d, 0x5205, 0xedfa, 0x3c95, 0x836a,
                0xc67a, 0x7985, 0xa8ea, 0x1715, 0x874d, 0x38b2, 0xe9dd, 0x5622,
                0x41a4, 0xfe5b, 0x2f34, 0x90cb, 0x0093, 0xbf6c, 0x6e03, 0xd1fc,
                0x94ec, 0x2b13, 0xfa7c, 0x4583, 0xd5db, 0x6a24, 0xbb4b, 0x04b4,
                0x496c, 0xf693, 0x27fc, 0x9803, 0x085b, 0xb7a4, 0x66cb, 0xd934,
                0x9c24, 0x23db, 0xf2b4, 0x4d4b, 0xdd13, 0x62ec, 0xb383, 0x0c7c,
                0x1bfa, 0xa405, 0x756a, 0xca95, 0x5acd, 0xe532, 0x345d, 0x8ba2,
                0xceb2, 0x714d, 0xa022, 0x1fdd, 0x8f85, 0x307a, 0xe115, 0x5eea,
                0x98ef, 0x2710, 0xf67f, 0x4980, 0xd9d8, 0x6627, 0xb748, 0x08b7,
                0x4da7, 0xf258, 0x2337, 0x9cc8, 0x0c90, 0xb36f, 0x6200, 0xddff,
                0xca79, 0x7586, 0xa4e9, 0x1b16, 0x8b4e, 0x34b1, 0xe5de, 0x5a21,
                0x1f31, 0xa0ce, 0x71a1, 0xce5e, 0x5e06, 0xe1f9, 0x3096, 0x8f69,
                0x8bdd, 0x3422, 0xe54d, 0x5ab2, 0xcaea, 0x7515, 0xa47a, 0x1b85,
                0x5e95, 0xe16a, 0x3005, 0x8ffa, 0x1fa2, 0xa05d, 0x7132, 0xcecd,
                0xd94b, 0x66b4, 0xb7db, 0x0824, 0x987c, 0x2783, 0xf6ec, 0x4913,
                0x0c03, 0xb3fc, 0x6293, 0xdd6c, 0x4d34, 0xf2cb, 0x23a4, 0x9c5b,
                0x5a5e, 0xe5a1, 0x34ce, 0x8b31, 0x1b69, 0xa496, 0x75f9, 0xca06,
                0x8f16, 0x30e9, 0xe186, 0x5e79, 0xce21, 0x71de, 0xa0b1, 0x1f4e,
                0x08c8, 0xb737, 0x6658, 0xd9a7, 0x49ff, 0xf600, 0x276f, 0x9890,
                0xdd80, 0x627f, 0xb310, 0x0cef, 0x9cb7, 0x2348, 0xf227, 0x4dd8
        };

        LBOX_WORD LBox2[256] = {
                0x0000, 0x74c2, 0xd324, 0xa7e6, 0xce28, 0xbaea, 0x1d0c, 0x69ce,
                0x6856, 0x1c94, 0xbb72, 0xcfb0, 0xa67e, 0xd2bc, 0x755a, 0x0198,
                0xe489, 0x904b, 0x37ad, 0x436f, 0x2aa1, 0x5e63, 0xf985, 0x8d47,
                0x8cdf, 0xf81d, 0x5ffb, 0x2b39, 0x42f7, 0x3635, 0x91d3, 0xe511,
                0x6839, 0x1cfb, 0xbb1d, 0xcfdf, 0xa611, 0xd2d3, 0x7535, 0x01f7,
                0x006f, 0x74ad, 0xd34b, 0xa789, 0xce47, 0xba85, 0x1d63, 0x69a1,
                0x8cb0, 0xf872, 0x5f94, 0x2b56, 0x4298, 0x365a, 0x91bc, 0xe57e,
                0xe4e6, 0x9024, 0x37c2, 0x4300, 0x2ace, 0x5e0c, 0xf9ea, 0x8d28,
                0x5e44, 0x2a86, 0x8d60, 0xf9a2, 0x906c, 0xe4ae, 0x4348, 0x378a,
                0x3612, 0x42d0, 0xe536, 0x91f4, 0xf83a, 0x8cf8, 0x2b1e, 0x5fdc,
                0xbacd, 0xce0f, 0x69e9, 0x1d2b, 0x74e5, 0x0027, 0xa7c1, 0xd303,
                0xd29b, 0xa659, 0x01bf, 0x757d, 0x1cb3, 0x6871, 0xcf97, 0xbb55,
                0x367d, 0x42bf, 0xe559, 0x919b, 0xf855, 0x8c97, 0x2b71, 0x5fb3,
                0x5e2b, 0x2ae9, 0x8d0f, 0xf9cd, 0x9003, 0xe4c1, 0x4327, 0x37e5,
                0xd2f4, 0xa636, 0x01d0, 0x7512, 0x1cdc, 0x681e, 0xcff8, 0xbb3a,
                0xbaa2, 0xce60, 0x6986, 0x1d44, 0x748a, 0x0048, 0xa7ae, 0xd36c,
                0x614b, 0x1589, 0xb26f, 0xc6ad, 0xaf63, 0xdba1, 0x7c47, 0x0885,
                0x091d, 0x7ddf, 0xda39, 0xaefb, 0xc735, 0xb3f7, 0x1411, 0x60d3,
                0x85c2, 0xf100, 0x56e6, 0x2224, 0x4bea, 0x3f28, 0x98ce, 0xec0c,
                0xed94, 0x9956, 0x3eb0, 0x4a72, 0x23bc, 0x577e, 0xf098, 0x845a,
                0x0972, 0x7db0, 0xda56, 0xae94, 0xc75a, 0xb398, 0x147e, 0x60bc,
                0x6124, 0x15e6, 0xb200, 0xc6c2, 0xaf0c, 0xdbce, 0x7c28, 0x08ea,
                0xedfb, 0x9939, 0x3edf, 0x4a1d, 0x23d3, 0x5711, 0xf0f7, 0x8435,
                0x85ad, 0xf16f, 0x5689, 0x224b, 0x4b85, 0x3f47, 0x98a1, 0xec63,
                0x3f0f, 0x4bcd, 0xec2b, 0x98e9, 0xf127, 0x85e5, 0x2203, 0x56c1,
                0x5759, 0x239b, 0x847d, 0xf0bf, 0x9971, 0xedb3, 0x4a55, 0x3e97,
                0xdb86, 0xaf44, 0x08a2, 0x7c60, 0x15ae, 0x616c, 0xc68a, 0xb248,
                0xb3d0, 0xc712, 0x60f4, 0x1436, 0x7df8, 0x093a, 0xaedc, 0xda1e,
                0x5736, 0x23f4, 0x8412, 0xf0d0, 0x991e, 0xeddc, 0x4a3a, 0x3ef8,
                0x3f60, 0x4ba2, 0xec44, 0x9886, 0xf148, 0x858a, 0x226c, 0x56ae,
                0xb3bf, 0xc77d, 0x609b, 0x1459, 0x7d97, 0x0955, 0xaeb3, 0xda71,
                0xdbe9, 0xaf2b, 0x08cd, 0x7c0f, 0x15c1, 0x6103, 0xc6e5, 0xb227,
        };

        LBOX_INV_WORD LBoxInv1[256] = {
                0x0000, 0xb065, 0x8935, 0x3950, 0x4a95, 0xfaf0, 0xc3a0, 0x73c5,
                0xb489, 0x04ec, 0x3dbc, 0x8dd9, 0xfe1c, 0x4e79, 0x7729, 0xc74c,
                0x2857, 0x9832, 0xa162, 0x1107, 0x62c2, 0xd2a7, 0xebf7, 0x5b92,
                0x9cde, 0x2cbb, 0x15eb, 0xa58e, 0xd64b, 0x662e, 0x5f7e, 0xef1b,
                0x26c5, 0x96a0, 0xaff0, 0x1f95, 0x6c50, 0xdc35, 0xe565, 0x5500,
                0x924c, 0x2229, 0x1b79, 0xab1c, 0xd8d9, 0x68bc, 0x51ec, 0xe189,
                0x0e92, 0xbef7, 0x87a7, 0x37c2, 0x4407, 0xf462, 0xcd32, 0x7d57,
                0xba1b, 0x0a7e, 0x332e, 0x834b, 0xf08e, 0x40eb, 0x79bb, 0xc9de,
                0xc989, 0x79ec, 0x40bc, 0xf0d9, 0x831c, 0x3379, 0x0a29, 0xba4c,
                0x7d00, 0xcd65, 0xf435, 0x4450, 0x3795, 0x87f0, 0xbea0, 0x0ec5,
                0xe1de, 0x51bb, 0x68eb, 0xd88e, 0xab4b, 0x1b2e, 0x227e, 0x921b,
                0x5557, 0xe532, 0xdc62, 0x6c07, 0x1fc2, 0xafa7, 0x96f7, 0x2692,
                0xef4c, 0x5f29, 0x6679, 0xd61c, 0xa5d9, 0x15bc, 0x2cec, 0x9c89,
                0x5bc5, 0xeba0, 0xd2f0, 0x6295, 0x1150, 0xa135, 0x9865, 0x2800,
                0xc71b, 0x777e, 0x4e2e, 0xfe4b, 0x8d8e, 0x3deb, 0x04bb, 0xb4de,
                0x7392, 0xc3f7, 0xfaa7, 0x4ac2, 0x3907, 0x8962, 0xb032, 0x0057,
                0x1173, 0xa116, 0x9846, 0x2823, 0x5be6, 0xeb83, 0xd2d3, 0x62b6,
                0xa5fa, 0x159f, 0x2ccf, 0x9caa, 0xef6f, 0x5f0a, 0x665a, 0xd63f,
                0x3924, 0x8941, 0xb011, 0x0074, 0x73b1, 0xc3d4, 0xfa84, 0x4ae1,
                0x8dad, 0x3dc8, 0x0498, 0xb4fd, 0xc738, 0x775d, 0x4e0d, 0xfe68,
                0x37b6, 0x87d3, 0xbe83, 0x0ee6, 0x7d23, 0xcd46, 0xf416, 0x4473,
                0x833f, 0x335a, 0x0a0a, 0xba6f, 0xc9aa, 0x79cf, 0x409f, 0xf0fa,
                0x1fe1, 0xaf84, 0x96d4, 0x26b1, 0x5574, 0xe511, 0xdc41, 0x6c24,
                0xab68, 0x1b0d, 0x225d, 0x9238, 0xe1fd, 0x5198, 0x68c8, 0xd8ad,
                0xd8fa, 0x689f, 0x51cf, 0xe1aa, 0x926f, 0x220a, 0x1b5a, 0xab3f,
                0x6c73, 0xdc16, 0xe546, 0x5523, 0x26e6, 0x9683, 0xafd3, 0x1fb6,
                0xf0ad, 0x40c8, 0x7998, 0xc9fd, 0xba38, 0x0a5d, 0x330d, 0x8368,
                0x4424, 0xf441, 0xcd11, 0x7d74, 0x0eb1, 0xbed4, 0x8784, 0x37e1,
                0xfe3f, 0x4e5a, 0x770a, 0xc76f, 0xb4aa, 0x04cf, 0x3d9f, 0x8dfa,
                0x4ab6, 0xfad3, 0xc383, 0x73e6, 0x0023, 0xb046, 0x8916, 0x3973,
                0xd668, 0x660d, 0x5f5d, 0xef38, 0x9cfd, 0x2c98, 0x15c8, 0xa5ad,
                0x62e1, 0xd284, 0xebd4, 0x5bb1, 0x2874, 0x9811, 0xa141, 0x1124,
        };

        LBOX_INV_WORD LBoxInv2[256] = {
                0x0000, 0x82ad, 0x4653, 0xc4fe, 0x550b, 0xd7a6, 0x1358, 0x91f5,
                0x6c83, 0xee2e, 0x2ad0, 0xa87d, 0x3988, 0xbb25, 0x7fdb, 0xfd76,
                0x4339, 0xc194, 0x056a, 0x87c7, 0x1632, 0x949f, 0x5061, 0xd2cc,
                0x2fba, 0xad17, 0x69e9, 0xeb44, 0x7ab1, 0xf81c, 0x3ce2, 0xbe4f,
                0xb903, 0x3bae, 0xff50, 0x7dfd, 0xec08, 0x6ea5, 0xaa5b, 0x28f6,
                0xd580, 0x572d, 0x93d3, 0x117e, 0x808b, 0x0226, 0xc6d8, 0x4475,
                0xfa3a, 0x7897, 0xbc69, 0x3ec4, 0xaf31, 0x2d9c, 0xe962, 0x6bcf,
                0x96b9, 0x1414, 0xd0ea, 0x5247, 0xc3b2, 0x411f, 0x85e1, 0x074c,
                0xfffe, 0x7d53, 0xb9ad, 0x3b00, 0xaaf5, 0x2858, 0xeca6, 0x6e0b,
                0x937d, 0x11d0, 0xd52e, 0x5783, 0xc676, 0x44db, 0x8025, 0x0288,
                0xbcc7, 0x3e6a, 0xfa94, 0x7839, 0xe9cc, 0x6b61, 0xaf9f, 0x2d32,
                0xd044, 0x52e9, 0x9617, 0x14ba, 0x854f, 0x07e2, 0xc31c, 0x41b1,
                0x46fd, 0xc450, 0x00ae, 0x8203, 0x13f6, 0x915b, 0x55a5, 0xd708,
                0x2a7e, 0xa8d3, 0x6c2d, 0xee80, 0x7f75, 0xfdd8, 0x3926, 0xbb8b,
                0x05c4, 0x8769, 0x4397, 0xc13a, 0x50cf, 0xd262, 0x169c, 0x9431,
                0x6947, 0xebea, 0x2f14, 0xadb9, 0x3c4c, 0xbee1, 0x7a1f, 0xf8b2,
                0x1669, 0x94c4, 0x503a, 0xd297, 0x4362, 0xc1cf, 0x0531, 0x879c,
                0x7aea, 0xf847, 0x3cb9, 0xbe14, 0x2fe1, 0xad4c, 0x69b2, 0xeb1f,
                0x5550, 0xd7fd, 0x1303, 0x91ae, 0x005b, 0x82f6, 0x4608, 0xc4a5,
                0x39d3, 0xbb7e, 0x7f80, 0xfd2d, 0x6cd8, 0xee75, 0x2a8b, 0xa826,
                0xaf6a, 0x2dc7, 0xe939, 0x6b94, 0xfa61, 0x78cc, 0xbc32, 0x3e9f,
                0xc3e9, 0x4144, 0x85ba, 0x0717, 0x96e2, 0x144f, 0xd0b1, 0x521c,
                0xec53, 0x6efe, 0xaa00, 0x28ad, 0xb958, 0x3bf5, 0xff0b, 0x7da6,
                0x80d0, 0x027d, 0xc683, 0x442e, 0xd5db, 0x5776, 0x9388, 0x1125,
                0xe997, 0x6b3a, 0xafc4, 0x2d69, 0xbc9c, 0x3e31, 0xfacf, 0x7862,
                0x8514, 0x07b9, 0xc347, 0x41ea, 0xd01f, 0x52b2, 0x964c, 0x14e1,
                0xaaae, 0x2803, 0xecfd, 0x6e50, 0xffa5, 0x7d08, 0xb9f6, 0x3b5b,
                0xc62d, 0x4480, 0x807e, 0x02d3, 0x9326, 0x118b, 0xd575, 0x57d8,
                0x5094, 0xd239, 0x16c7, 0x946a, 0x059f, 0x8732, 0x43cc, 0xc161,
                0x3c17, 0xbeba, 0x7a44, 0xf8e9, 0x691c, 0xebb1, 0x2f4f, 0xade2,
                0x13ad, 0x9100, 0x55fe, 0xd753, 0x46a6, 0xc40b, 0x00f5, 0x8258,
                0x7f2e, 0xfd83, 0x397d, 0xbbd0, 0x2a25, 0xa888, 0x6c76, 0xeedb,
        };
    public:
        fantomas(size_t rounds) : lightweight(rounds) {};

        void Encrypt(uint8_t *block) override;

        void Decrypt(uint8_t *block) override;
    };

}
