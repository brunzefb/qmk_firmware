enum unicode_names {
  U_SS_LOWER,
  U_SS_UPPER,
  U_NTIL_LOWER,
  U_NTIL_UPPER,
  U_CCED_LOWER,
  U_CCED_UPPER,
  U_IQUE_SYM,
};

const uint32_t unicode_map[] PROGMEM = {
  [U_SS_LOWER]   = 0x00df,  // ß
  [U_SS_UPPER]   = 0x1e9e,  // ẞ
  [U_NTIL_LOWER] = 0x00f1,  // ñ
  [U_NTIL_UPPER] = 0x00d1,  // Ñ
  [U_CCED_LOWER] = 0x00e7,  // ç
  [U_CCED_UPPER] = 0x00c7,  // Ç
  [U_IQUE_SYM]   = 0x00bf,  // ¿
  // [U_AIG_A_LOWER] = 0x00e1,  // á
  // [U_AIG_A_UPPER] = 0x00c1,  // Á
  // [U_AIG_E_LOWER] = 0x00e9,  // é
  // [U_AIG_E_UPPER] = 0x00c9,  // É
  // [U_GRAV_A_LOWER] = 0x,  // 
  // [U_GRAV_A_UPPER] = 0x,  // 
  // [U_GRAV_E_LOWER] = 0x,  // 
  // [U_GRAV_E_UPPER] = 0x,  // 

};

#define U_SS XP(U_SS_LOWER, U_SS_UPPER)
// ñ and Ñ keycode.
#define U_NTIL XP(U_NTIL_LOWER, U_NTIL_UPPER)
// ç and Ç keycode.
#define U_CCED XP(U_CCED_LOWER, U_CCED_UPPER)
// ¿ keycode.
#define U_IQUE X(U_IQUE_SYM)
