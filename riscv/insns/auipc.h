#ifdef CHERI_MERGED_RF
if (CHERI->get_mode()) {
  cheri_reg_t pcc_temp = PCC;
  pcc_temp.offset = insn.u_imm() + pc;
  WRITE_CD(pcc_temp);
} else {
  WRITE_RD(sext_xlen(insn.u_imm() + pc));
}
#else
WRITE_RD(sext_xlen(insn.u_imm() + pc));
#endif
