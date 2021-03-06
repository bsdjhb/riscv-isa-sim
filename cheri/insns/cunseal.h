// See LICENSE_CHERI for license details.

if (!CS1.tag) {
  CHERI->raise_trap(CAUSE_CHERI_TAG_FAULT, insn.cs1());
} else if (!CS2.tag) {
  CHERI->raise_trap(CAUSE_CHERI_TAG_FAULT, insn.cs2());
} else if (!CS1.sealed()) {
  CHERI->raise_trap(CAUSE_CHERI_SEAL_FAULT, insn.cs1());
} else if (CS2.sealed()) {
  CHERI->raise_trap(CAUSE_CHERI_SEAL_FAULT, insn.cs2());
} else if (CS2.cursor() != CS1.otype) {
  CHERI->raise_trap(CAUSE_CHERI_TYPE_FAULT, insn.cs2());
} else if (!(CS2.perms & BIT(CHERI_PERMIT_UNSEAL))) {
  CHERI->raise_trap(CAUSE_CHERI_PERMIT_UNSEAL_FAULT, insn.cs2());
} else if (CS2.cursor() < CS2.base()) {
  CHERI->raise_trap(CAUSE_CHERI_LENGTH_FAULT, insn.cs2());
} else if (CS2.cursor() >= CS2.top()) {
  CHERI->raise_trap(CAUSE_CHERI_LENGTH_FAULT, insn.cs2());
} else {
  cheri_reg_t temp = CS1;
  temp.otype = OTYPE_UNSEALED;
  temp.perms &= CS2.perms | ~BIT(CHERI_PERMIT_GLOBAL);
  WRITE_CD(temp);
}
