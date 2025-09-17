// Copyright 2022 Manna Harbour
// https://github.com/manna-harbour/miryoku

#include "zmk-helpers/key-labels/42.h"

#define KEYS_L LT0 LT1 LT2 LT3 LT4 LM0 LM1 LM2 LM3 LM4 LB0 LB1 LB2 LB3 LB4  // left-hand keys
#define KEYS_R RT0 RT1 RT2 RT3 RT4 RM0 RM1 RM2 RM3 RM4 RB0 RB1 RB2 RB3 RB4  // right-hand keys
#define THUMBS LH2 LH1 LH0 RH0 RH1 RH2                                      // thumb keys

#pragma once

#define U_MACRO_VA_ARGS(macro, ...) macro(__VA_ARGS__)
#define U_STRINGIFY(x) #x
#define U_MACRO(name,...) \
/ { \
  macros { \
    name: name { \
      compatible = "zmk,behavior-macro"; \
      #binding-cells = <0>; \
      __VA_ARGS__ \
    }; \
  }; \
};

#define MIRYOKU_TAPDELAY_TAP(CODE) \
U_MACRO(u_tapdelay_tap_##CODE, bindings = <&macro_press &kp CODE>, <&macro_release &kp CODE>;)

#define MIRYOKU_TAPDELAY_MT_L(CODE) \
/ { \
  behaviors { \
    u_tapdelay_mt_l_##CODE: u_tapdelay_mt_l_##CODE { \
      compatible = "zmk,behavior-hold-tap"; \
      #binding-cells = <2>; \
      tapping-term-ms = <U_TAPPING_TERM>; \
      require-prior-idle-ms = <150>; \
      flavor = "balanced"; \
      bindings = <&kp>, <&u_tapdelay_tap_##CODE>; \
      hold-trigger-key-positions = <KEYS_R THUMBS>; \
      hold-trigger-on-release; \
    }; \
  }; \
};

#define MIRYOKU_TAPDELAY_MT_R(CODE) \
/ { \
  behaviors { \
    u_tapdelay_mt_r_##CODE: u_tapdelay_mt_r_##CODE { \
      compatible = "zmk,behavior-hold-tap"; \
      #binding-cells = <2>; \
      tapping-term-ms = <U_TAPPING_TERM>; \
      require-prior-idle-ms = <150>; \
      flavor = "balanced"; \
      bindings = <&kp>, <&u_tapdelay_tap_##CODE>; \
      hold-trigger-key-positions = <KEYS_L THUMBS>; \
      hold-trigger-on-release; \
    }; \
  }; \
};

#define MIRYOKU_TAPDELAY_LT(CODE) \
/ { \
  behaviors { \
    u_tapdelay_lt_##CODE: u_tapdelay_lt_##CODE { \
      compatible = "zmk,behavior-hold-tap"; \
      #binding-cells = <2>; \
      tapping-term-ms = <U_TAPPING_TERM>; \
      flavor = "tap-preferred"; \
      bindings = <&mo>, <&u_tapdelay_tap_##CODE>; \
    }; \
  }; \
};

#define U_MT_L(MOD, TAP) &u_tapdelay_mt_l_##TAP MOD 0
#define U_MT_R(MOD, TAP) &u_tapdelay_mt_r_##TAP MOD 0
#define U_LT(LAYER, TAP) &u_tapdelay_lt_##TAP LAYER 0

#define MIRYOKU_TAPDELAY_LIST \
MIRYOKU_X(A,) \
MIRYOKU_X(B,) \
MIRYOKU_X(C,) \
MIRYOKU_X(D,) \
MIRYOKU_X(E,) \
MIRYOKU_X(F,) \
MIRYOKU_X(G,) \
MIRYOKU_X(H,) \
MIRYOKU_X(I,) \
MIRYOKU_X(J,) \
MIRYOKU_X(K,) \
MIRYOKU_X(L,) \
MIRYOKU_X(M,) \
MIRYOKU_X(N,) \
MIRYOKU_X(O,) \
MIRYOKU_X(P,) \
MIRYOKU_X(Q,) \
MIRYOKU_X(R,) \
MIRYOKU_X(S,) \
MIRYOKU_X(T,) \
MIRYOKU_X(U,) \
MIRYOKU_X(V,) \
MIRYOKU_X(W,) \
MIRYOKU_X(X,) \
MIRYOKU_X(Y,) \
MIRYOKU_X(Z,) \
MIRYOKU_X(SQT,) \
MIRYOKU_X(COMMA,) \
MIRYOKU_X(DOT,) \
MIRYOKU_X(SLASH,) \
MIRYOKU_X(ESC,) \
MIRYOKU_X(SPACE,) \
MIRYOKU_X(TAB,) \
MIRYOKU_X(RET,) \
MIRYOKU_X(BSPC,) \
MIRYOKU_X(DEL,)
