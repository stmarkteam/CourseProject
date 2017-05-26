#include "function.h"

const int H = 28;
const int W = 133;

String TileMap[H] = {
"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
"000000000000000000000000000000000000000ZrZ0000000000000000000000000000000000                                  0000000000000000000Zr0",
"000000000000000000000000000000000000000ZZZ0000000000000000000000000000000000                                  0000000000000000000ZZ0",
"0                                                    PP                                       r                        P           0",
"0r                    r                             PP r                                                               P           0",
"0ww                                                PP                                                                  P          P0",
"0          r   PPP                      P          PP       PPPP     Pnnn       P             P                      r P         P 0",
"0        PPPPP              r                       PP r                            r    P         P    r           PPPP     PP    0",
"0     P                   PPPPP                      PPPP          P      P  P      P                   P   P                      0",
"0                   r                P                                       wqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqw             PP       0",
"0r                PPPPP                                          P           wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww   P                  0",
"0P  P                                       P                                                               Z       r   r          0",
"0                         w  r    P                         PP                            r          r      Z       PPPPP          0",
"0    P                    w            r                   PPPP                                             Z                      0",
"0               ww        w           PP         P        PPPPPP                          w          w      Z                      0",
"0      P    w   ww   w    wrrw     P                 P   PPPPPPPP      w    w                              rw  P   P  r   P       r0",
"qqqqqqqwwwwwwqqqwwqqqwwwwwwwwwqqqqqqqqqqqqqqqqqqqqqqqqqqqwwwwwwwwwwwwwwwqqqqw         w       w   w      wwwwqqqqqqPPPPPPPPqqqqqqPPP",
"qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqwwwwwwwwwwwqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq",
"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
};
