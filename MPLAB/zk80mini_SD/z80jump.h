/*
   This program is provided under the LGPL license ver 2.
   Written by Katsumi.
   http://hp.vector.co.jp/authors/VA016157/
   kmorimatsu@users.sourceforge.jp
*/

void execZ80infinite(){
	UINT8 code;
	while(1) {
		code=_getCode();
		execZ80(code);
	}
}
void execZ80code(){
	UINT8 code;
	code=_getCode();
	execZ80(code);
	if (z80irq) doZ80Int();
}
void execZ80(UINT8 code){
	if (!(code&0x80)) {
		if (!(code&0x40)) {
			if (!(code&0x20)) {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									code00();
								} else {
									code01();
								}
							} else {
								if (!(code&0x1)) {
									code02();
								} else {
									code03();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									code04();
								} else {
									code05();
								}
							} else {
								if (!(code&0x1)) {
									code06();
								} else {
									code07();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									#ifdef Z80
										code08();
									#endif
									#ifdef I8080
										codeVOID();
									#endif
								} else {
									code09();
								}
							} else {
								if (!(code&0x1)) {
									code0A();
								} else {
									code0B();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									code0C();
								} else {
									code0D();
								}
							} else {
								if (!(code&0x1)) {
									code0E();
								} else {
									code0F();
								}
							}
						}
					}
				} else {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									#ifdef Z80
										code10();
									#endif
									#ifdef I8080
										codeVOID();
									#endif
								} else {
									code11();
								}
							} else {
								if (!(code&0x1)) {
									code12();
								} else {
									code13();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									code14();
								} else {
									code15();
								}
							} else {
								if (!(code&0x1)) {
									code16();
								} else {
									code17();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									#ifdef Z80
										code18();
									#endif
									#ifdef I8080
										codeVOID();
									#endif
								} else {
									code19();
								}
							} else {
								if (!(code&0x1)) {
									code1A();
								} else {
									code1B();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									code1C();
								} else {
									code1D();
								}
							} else {
								if (!(code&0x1)) {
									code1E();
								} else {
									code1F();
								}
							}
						}
					}
				}
			} else {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									#ifdef Z80
										code20();
									#endif
									#ifdef I8080
										codeVOID();
									#endif
								} else {
									code21();
								}
							} else {
								if (!(code&0x1)) {
									code22();
								} else {
									code23();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									code24();
								} else {
									code25();
								}
							} else {
								if (!(code&0x1)) {
									code26();
								} else {
									code27();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									#ifdef Z80
										code28();
									#endif
									#ifdef I8080
										codeVOID();
									#endif
								} else {
									code29();
								}
							} else {
								if (!(code&0x1)) {
									code2A();
								} else {
									code2B();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									code2C();
								} else {
									code2D();
								}
							} else {
								if (!(code&0x1)) {
									code2E();
								} else {
									code2F();
								}
							}
						}
					}
				} else {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									#ifdef Z80
										code30();
									#endif
									#ifdef I8080
										codeVOID();
									#endif
								} else {
									code31();
								}
							} else {
								if (!(code&0x1)) {
									code32();
								} else {
									code33();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									code34();
								} else {
									code35();
								}
							} else {
								if (!(code&0x1)) {
									code36();
								} else {
									code37();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									#ifdef Z80
										code38();
									#endif
									#ifdef I8080
										codeVOID();
									#endif
								} else {
									code39();
								}
							} else {
								if (!(code&0x1)) {
									code3A();
								} else {
									code3B();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									code3C();
								} else {
									code3D();
								}
							} else {
								if (!(code&0x1)) {
									code3E();
								} else {
									code3F();
								}
							}
						}
					}
				}
			}
		} else {
			if (!(code&0x20)) {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									code40();
								} else {
									code41();
								}
							} else {
								if (!(code&0x1)) {
									code42();
								} else {
									code43();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									code44();
								} else {
									code45();
								}
							} else {
								if (!(code&0x1)) {
									code46();
								} else {
									code47();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									code48();
								} else {
									code49();
								}
							} else {
								if (!(code&0x1)) {
									code4A();
								} else {
									code4B();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									code4C();
								} else {
									code4D();
								}
							} else {
								if (!(code&0x1)) {
									code4E();
								} else {
									code4F();
								}
							}
						}
					}
				} else {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									code50();
								} else {
									code51();
								}
							} else {
								if (!(code&0x1)) {
									code52();
								} else {
									code53();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									code54();
								} else {
									code55();
								}
							} else {
								if (!(code&0x1)) {
									code56();
								} else {
									code57();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									code58();
								} else {
									code59();
								}
							} else {
								if (!(code&0x1)) {
									code5A();
								} else {
									code5B();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									code5C();
								} else {
									code5D();
								}
							} else {
								if (!(code&0x1)) {
									code5E();
								} else {
									code5F();
								}
							}
						}
					}
				}
			} else {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									code60();
								} else {
									code61();
								}
							} else {
								if (!(code&0x1)) {
									code62();
								} else {
									code63();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									code64();
								} else {
									code65();
								}
							} else {
								if (!(code&0x1)) {
									code66();
								} else {
									code67();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									code68();
								} else {
									code69();
								}
							} else {
								if (!(code&0x1)) {
									code6A();
								} else {
									code6B();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									code6C();
								} else {
									code6D();
								}
							} else {
								if (!(code&0x1)) {
									code6E();
								} else {
									code6F();
								}
							}
						}
					}
				} else {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									code70();
								} else {
									code71();
								}
							} else {
								if (!(code&0x1)) {
									code72();
								} else {
									code73();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									code74();
								} else {
									code75();
								}
							} else {
								if (!(code&0x1)) {
									code76();
								} else {
									code77();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									code78();
								} else {
									code79();
								}
							} else {
								if (!(code&0x1)) {
									code7A();
								} else {
									code7B();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									code7C();
								} else {
									code7D();
								}
							} else {
								if (!(code&0x1)) {
									code7E();
								} else {
									code7F();
								}
							}
						}
					}
				}
			}
		}
	} else {
		if (!(code&0x40)) {
			if (!(code&0x20)) {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									code80();
								} else {
									code81();
								}
							} else {
								if (!(code&0x1)) {
									code82();
								} else {
									code83();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									code84();
								} else {
									code85();
								}
							} else {
								if (!(code&0x1)) {
									code86();
								} else {
									code87();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									code88();
								} else {
									code89();
								}
							} else {
								if (!(code&0x1)) {
									code8A();
								} else {
									code8B();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									code8C();
								} else {
									code8D();
								}
							} else {
								if (!(code&0x1)) {
									code8E();
								} else {
									code8F();
								}
							}
						}
					}
				} else {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									code90();
								} else {
									code91();
								}
							} else {
								if (!(code&0x1)) {
									code92();
								} else {
									code93();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									code94();
								} else {
									code95();
								}
							} else {
								if (!(code&0x1)) {
									code96();
								} else {
									code97();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									code98();
								} else {
									code99();
								}
							} else {
								if (!(code&0x1)) {
									code9A();
								} else {
									code9B();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									code9C();
								} else {
									code9D();
								}
							} else {
								if (!(code&0x1)) {
									code9E();
								} else {
									code9F();
								}
							}
						}
					}
				}
			} else {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeA0();
								} else {
									codeA1();
								}
							} else {
								if (!(code&0x1)) {
									codeA2();
								} else {
									codeA3();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeA4();
								} else {
									codeA5();
								}
							} else {
								if (!(code&0x1)) {
									codeA6();
								} else {
									codeA7();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeA8();
								} else {
									codeA9();
								}
							} else {
								if (!(code&0x1)) {
									codeAA();
								} else {
									codeAB();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeAC();
								} else {
									codeAD();
								}
							} else {
								if (!(code&0x1)) {
									codeAE();
								} else {
									codeAF();
								}
							}
						}
					}
				} else {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeB0();
								} else {
									codeB1();
								}
							} else {
								if (!(code&0x1)) {
									codeB2();
								} else {
									codeB3();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeB4();
								} else {
									codeB5();
								}
							} else {
								if (!(code&0x1)) {
									codeB6();
								} else {
									codeB7();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeB8();
								} else {
									codeB9();
								}
							} else {
								if (!(code&0x1)) {
									codeBA();
								} else {
									codeBB();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeBC();
								} else {
									codeBD();
								}
							} else {
								if (!(code&0x1)) {
									codeBE();
								} else {
									codeBF();
								}
							}
						}
					}
				}
			}
		} else {
			if (!(code&0x20)) {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeC0();
								} else {
									codeC1();
								}
							} else {
								if (!(code&0x1)) {
									codeC2();
								} else {
									codeC3();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeC4();
								} else {
									codeC5();
								}
							} else {
								if (!(code&0x1)) {
									codeC6();
								} else {
									codeC7();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeC8();
								} else {
									codeC9();
								}
							} else {
								if (!(code&0x1)) {
									codeCA();
								} else {
									#ifdef Z80
										codeCB();
									#endif
									#ifdef I8080
										codeVOID();
									#endif
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCC();
								} else {
									codeCD();
								}
							} else {
								if (!(code&0x1)) {
									codeCE();
								} else {
									codeCF();
								}
							}
						}
					}
				} else {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeD0();
								} else {
									codeD1();
								}
							} else {
								if (!(code&0x1)) {
									codeD2();
								} else {
									codeD3();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeD4();
								} else {
									codeD5();
								}
							} else {
								if (!(code&0x1)) {
									codeD6();
								} else {
									codeD7();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeD8();
								} else {
									#ifdef Z80
										codeD9();
									#endif
									#ifdef I8080
										codeVOID();
									#endif
								}
							} else {
								if (!(code&0x1)) {
									codeDA();
								} else {
									codeDB();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeDC();
								} else {
									#ifdef Z80
										codeDD();
									#endif
									#ifdef I8080
										codeVOID();
									#endif
								}
							} else {
								if (!(code&0x1)) {
									codeDE();
								} else {
									codeDF();
								}
							}
						}
					}
				}
			} else {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeE0();
								} else {
									codeE1();
								}
							} else {
								if (!(code&0x1)) {
									codeE2();
								} else {
									codeE3();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeE4();
								} else {
									codeE5();
								}
							} else {
								if (!(code&0x1)) {
									codeE6();
								} else {
									codeE7();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeE8();
								} else {
									codeE9();
								}
							} else {
								if (!(code&0x1)) {
									codeEA();
								} else {
									codeEB();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeEC();
								} else {
									#ifdef Z80
										codeED();
									#endif
									#ifdef I8080
										codeVOID();
									#endif
								}
							} else {
								if (!(code&0x1)) {
									codeEE();
								} else {
									codeEF();
								}
							}
						}
					}
				} else {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeF0();
								} else {
									codeF1();
								}
							} else {
								if (!(code&0x1)) {
									codeF2();
								} else {
									codeF3();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeF4();
								} else {
									codeF5();
								}
							} else {
								if (!(code&0x1)) {
									codeF6();
								} else {
									codeF7();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeF8();
								} else {
									codeF9();
								}
							} else {
								if (!(code&0x1)) {
									codeFA();
								} else {
									codeFB();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeFC();
								} else {
									#ifdef Z80
										codeFD();
									#endif
									#ifdef I8080
										codeVOID();
									#endif
								}
							} else {
								if (!(code&0x1)) {
									codeFE();
								} else {
									codeFF();
								}
							}
						}
					}
				}
			}
		}
	}
}
//*/
#ifdef Z80
void codeCB(){
	UINT8 code=_getCode();
	if (!(code&0x80)) {
		if (!(code&0x40)) {
			if (!(code&0x20)) {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCB00();
								} else {
									codeCB01();
								}
							} else {
								if (!(code&0x1)) {
									codeCB02();
								} else {
									codeCB03();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCB04();
								} else {
									codeCB05();
								}
							} else {
								if (!(code&0x1)) {
									codeCB06();
								} else {
									codeCB07();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCB08();
								} else {
									codeCB09();
								}
							} else {
								if (!(code&0x1)) {
									codeCB0A();
								} else {
									codeCB0B();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCB0C();
								} else {
									codeCB0D();
								}
							} else {
								if (!(code&0x1)) {
									codeCB0E();
								} else {
									codeCB0F();
								}
							}
						}
					}
				} else {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCB10();
								} else {
									codeCB11();
								}
							} else {
								if (!(code&0x1)) {
									codeCB12();
								} else {
									codeCB13();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCB14();
								} else {
									codeCB15();
								}
							} else {
								if (!(code&0x1)) {
									codeCB16();
								} else {
									codeCB17();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCB18();
								} else {
									codeCB19();
								}
							} else {
								if (!(code&0x1)) {
									codeCB1A();
								} else {
									codeCB1B();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCB1C();
								} else {
									codeCB1D();
								}
							} else {
								if (!(code&0x1)) {
									codeCB1E();
								} else {
									codeCB1F();
								}
							}
						}
					}
				}
			} else {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCB20();
								} else {
									codeCB21();
								}
							} else {
								if (!(code&0x1)) {
									codeCB22();
								} else {
									codeCB23();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCB24();
								} else {
									codeCB25();
								}
							} else {
								if (!(code&0x1)) {
									codeCB26();
								} else {
									codeCB27();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCB28();
								} else {
									codeCB29();
								}
							} else {
								if (!(code&0x1)) {
									codeCB2A();
								} else {
									codeCB2B();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCB2C();
								} else {
									codeCB2D();
								}
							} else {
								if (!(code&0x1)) {
									codeCB2E();
								} else {
									codeCB2F();
								}
							}
						}
					}
				} else {
					if (!(code&0x8)) {
						codeVOID();
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCB38();
								} else {
									codeCB39();
								}
							} else {
								if (!(code&0x1)) {
									codeCB3A();
								} else {
									codeCB3B();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCB3C();
								} else {
									codeCB3D();
								}
							} else {
								if (!(code&0x1)) {
									codeCB3E();
								} else {
									codeCB3F();
								}
							}
						}
					}
				}
			}
		} else {
			if (!(code&0x20)) {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCB40();
								} else {
									codeCB41();
								}
							} else {
								if (!(code&0x1)) {
									codeCB42();
								} else {
									codeCB43();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCB44();
								} else {
									codeCB45();
								}
							} else {
								if (!(code&0x1)) {
									codeCB46();
								} else {
									codeCB47();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCB48();
								} else {
									codeCB49();
								}
							} else {
								if (!(code&0x1)) {
									codeCB4A();
								} else {
									codeCB4B();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCB4C();
								} else {
									codeCB4D();
								}
							} else {
								if (!(code&0x1)) {
									codeCB4E();
								} else {
									codeCB4F();
								}
							}
						}
					}
				} else {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCB50();
								} else {
									codeCB51();
								}
							} else {
								if (!(code&0x1)) {
									codeCB52();
								} else {
									codeCB53();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCB54();
								} else {
									codeCB55();
								}
							} else {
								if (!(code&0x1)) {
									codeCB56();
								} else {
									codeCB57();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCB58();
								} else {
									codeCB59();
								}
							} else {
								if (!(code&0x1)) {
									codeCB5A();
								} else {
									codeCB5B();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCB5C();
								} else {
									codeCB5D();
								}
							} else {
								if (!(code&0x1)) {
									codeCB5E();
								} else {
									codeCB5F();
								}
							}
						}
					}
				}
			} else {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCB60();
								} else {
									codeCB61();
								}
							} else {
								if (!(code&0x1)) {
									codeCB62();
								} else {
									codeCB63();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCB64();
								} else {
									codeCB65();
								}
							} else {
								if (!(code&0x1)) {
									codeCB66();
								} else {
									codeCB67();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCB68();
								} else {
									codeCB69();
								}
							} else {
								if (!(code&0x1)) {
									codeCB6A();
								} else {
									codeCB6B();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCB6C();
								} else {
									codeCB6D();
								}
							} else {
								if (!(code&0x1)) {
									codeCB6E();
								} else {
									codeCB6F();
								}
							}
						}
					}
				} else {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCB70();
								} else {
									codeCB71();
								}
							} else {
								if (!(code&0x1)) {
									codeCB72();
								} else {
									codeCB73();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCB74();
								} else {
									codeCB75();
								}
							} else {
								if (!(code&0x1)) {
									codeCB76();
								} else {
									codeCB77();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCB78();
								} else {
									codeCB79();
								}
							} else {
								if (!(code&0x1)) {
									codeCB7A();
								} else {
									codeCB7B();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCB7C();
								} else {
									codeCB7D();
								}
							} else {
								if (!(code&0x1)) {
									codeCB7E();
								} else {
									codeCB7F();
								}
							}
						}
					}
				}
			}
		}
	} else {
		if (!(code&0x40)) {
			if (!(code&0x20)) {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCB80();
								} else {
									codeCB81();
								}
							} else {
								if (!(code&0x1)) {
									codeCB82();
								} else {
									codeCB83();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCB84();
								} else {
									codeCB85();
								}
							} else {
								if (!(code&0x1)) {
									codeCB86();
								} else {
									codeCB87();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCB88();
								} else {
									codeCB89();
								}
							} else {
								if (!(code&0x1)) {
									codeCB8A();
								} else {
									codeCB8B();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCB8C();
								} else {
									codeCB8D();
								}
							} else {
								if (!(code&0x1)) {
									codeCB8E();
								} else {
									codeCB8F();
								}
							}
						}
					}
				} else {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCB90();
								} else {
									codeCB91();
								}
							} else {
								if (!(code&0x1)) {
									codeCB92();
								} else {
									codeCB93();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCB94();
								} else {
									codeCB95();
								}
							} else {
								if (!(code&0x1)) {
									codeCB96();
								} else {
									codeCB97();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCB98();
								} else {
									codeCB99();
								}
							} else {
								if (!(code&0x1)) {
									codeCB9A();
								} else {
									codeCB9B();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCB9C();
								} else {
									codeCB9D();
								}
							} else {
								if (!(code&0x1)) {
									codeCB9E();
								} else {
									codeCB9F();
								}
							}
						}
					}
				}
			} else {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCBA0();
								} else {
									codeCBA1();
								}
							} else {
								if (!(code&0x1)) {
									codeCBA2();
								} else {
									codeCBA3();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCBA4();
								} else {
									codeCBA5();
								}
							} else {
								if (!(code&0x1)) {
									codeCBA6();
								} else {
									codeCBA7();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCBA8();
								} else {
									codeCBA9();
								}
							} else {
								if (!(code&0x1)) {
									codeCBAA();
								} else {
									codeCBAB();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCBAC();
								} else {
									codeCBAD();
								}
							} else {
								if (!(code&0x1)) {
									codeCBAE();
								} else {
									codeCBAF();
								}
							}
						}
					}
				} else {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCBB0();
								} else {
									codeCBB1();
								}
							} else {
								if (!(code&0x1)) {
									codeCBB2();
								} else {
									codeCBB3();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCBB4();
								} else {
									codeCBB5();
								}
							} else {
								if (!(code&0x1)) {
									codeCBB6();
								} else {
									codeCBB7();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCBB8();
								} else {
									codeCBB9();
								}
							} else {
								if (!(code&0x1)) {
									codeCBBA();
								} else {
									codeCBBB();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCBBC();
								} else {
									codeCBBD();
								}
							} else {
								if (!(code&0x1)) {
									codeCBBE();
								} else {
									codeCBBF();
								}
							}
						}
					}
				}
			}
		} else {
			if (!(code&0x20)) {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCBC0();
								} else {
									codeCBC1();
								}
							} else {
								if (!(code&0x1)) {
									codeCBC2();
								} else {
									codeCBC3();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCBC4();
								} else {
									codeCBC5();
								}
							} else {
								if (!(code&0x1)) {
									codeCBC6();
								} else {
									codeCBC7();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCBC8();
								} else {
									codeCBC9();
								}
							} else {
								if (!(code&0x1)) {
									codeCBCA();
								} else {
									codeCBCB();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCBCC();
								} else {
									codeCBCD();
								}
							} else {
								if (!(code&0x1)) {
									codeCBCE();
								} else {
									codeCBCF();
								}
							}
						}
					}
				} else {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCBD0();
								} else {
									codeCBD1();
								}
							} else {
								if (!(code&0x1)) {
									codeCBD2();
								} else {
									codeCBD3();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCBD4();
								} else {
									codeCBD5();
								}
							} else {
								if (!(code&0x1)) {
									codeCBD6();
								} else {
									codeCBD7();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCBD8();
								} else {
									codeCBD9();
								}
							} else {
								if (!(code&0x1)) {
									codeCBDA();
								} else {
									codeCBDB();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCBDC();
								} else {
									codeCBDD();
								}
							} else {
								if (!(code&0x1)) {
									codeCBDE();
								} else {
									codeCBDF();
								}
							}
						}
					}
				}
			} else {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCBE0();
								} else {
									codeCBE1();
								}
							} else {
								if (!(code&0x1)) {
									codeCBE2();
								} else {
									codeCBE3();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCBE4();
								} else {
									codeCBE5();
								}
							} else {
								if (!(code&0x1)) {
									codeCBE6();
								} else {
									codeCBE7();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCBE8();
								} else {
									codeCBE9();
								}
							} else {
								if (!(code&0x1)) {
									codeCBEA();
								} else {
									codeCBEB();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCBEC();
								} else {
									codeCBED();
								}
							} else {
								if (!(code&0x1)) {
									codeCBEE();
								} else {
									codeCBEF();
								}
							}
						}
					}
				} else {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCBF0();
								} else {
									codeCBF1();
								}
							} else {
								if (!(code&0x1)) {
									codeCBF2();
								} else {
									codeCBF3();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCBF4();
								} else {
									codeCBF5();
								}
							} else {
								if (!(code&0x1)) {
									codeCBF6();
								} else {
									codeCBF7();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCBF8();
								} else {
									codeCBF9();
								}
							} else {
								if (!(code&0x1)) {
									codeCBFA();
								} else {
									codeCBFB();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeCBFC();
								} else {
									codeCBFD();
								}
							} else {
								if (!(code&0x1)) {
									codeCBFE();
								} else {
									codeCBFF();
								}
							}
						}
					}
				}
			}
		}
	}
}

void codeDD(){
	UINT8 code=_getCode();
	if (!(code&0x80)) {
		if (!(code&0x40)) {
			if (!(code&0x20)) {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						codeVOID();
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeVOID();
								} else {
									codeDD09();
								}
							} else {
								codeVOID();
							}
						} else {
							codeVOID();
						}
					}
				} else {
					if (!(code&0x8)) {
						codeVOID();
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeVOID();
								} else {
									codeDD19();
								}
							} else {
								codeVOID();
							}
						} else {
							codeVOID();
						}
					}
				}
			} else {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeVOID();
								} else {
									codeDD21();
								}
							} else {
								if (!(code&0x1)) {
									codeDD22();
								} else {
									codeDD23();
								}
							}
						} else {
							codeVOID();
						}
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeVOID();
								} else {
									codeDD29();
								}
							} else {
								if (!(code&0x1)) {
									codeDD2A();
								} else {
									codeDD2B();
								}
							}
						} else {
							codeVOID();
						}
					}
				} else {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeDD34();
								} else {
									codeDD35();
								}
							} else {
								if (!(code&0x1)) {
									codeDD36();
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeVOID();
								} else {
									codeDD39();
								}
							} else {
								codeVOID();
							}
						} else {
							codeVOID();
						}
					}
				}
			}
		} else {
			if (!(code&0x20)) {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDD46();
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDD4E();
								} else {
									codeVOID();
								}
							}
						}
					}
				} else {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDD56();
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDD5E();
								} else {
									codeVOID();
								}
							}
						}
					}
				}
			} else {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDD66();
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDD6E();
								} else {
									codeVOID();
								}
							}
						}
					}
				} else {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeDD70();
								} else {
									codeDD71();
								}
							} else {
								if (!(code&0x1)) {
									codeDD72();
								} else {
									codeDD73();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeDD74();
								} else {
									codeDD75();
								}
							} else {
								if (!(code&0x1)) {
									codeVOID();
								} else {
									codeDD77();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDD7E();
								} else {
									codeVOID();
								}
							}
						}
					}
				}
			}
		}
	} else {
		if (!(code&0x40)) {
			if (!(code&0x20)) {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDD86();
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDD8E();
								} else {
									codeVOID();
								}
							}
						}
					}
				} else {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDD96();
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDD9E();
								} else {
									codeVOID();
								}
							}
						}
					}
				}
			} else {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDDA6();
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDDAE();
								} else {
									codeVOID();
								}
							}
						}
					}
				} else {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDDB6();
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDDBE();
								} else {
									codeVOID();
								}
							}
						}
					}
				}
			}
		} else {
			if (!(code&0x20)) {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						codeVOID();
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeVOID();
								} else {
									codeDDCB();
								}
							}
						} else {
							codeVOID();
						}
					}
				} else {
					codeVOID();
				}
			} else {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeVOID();
								} else {
									codeDDE1();
								}
							} else {
								if (!(code&0x1)) {
									codeVOID();
								} else {
									codeDDE3();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeVOID();
								} else {
									codeDDE5();
								}
							} else {
								codeVOID();
							}
						}
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeVOID();
								} else {
									codeDDE9();
								}
							} else {
								codeVOID();
							}
						} else {
							codeVOID();
						}
					}
				} else {
					if (!(code&0x8)) {
						codeVOID();
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeVOID();
								} else {
									codeDDF9();
								}
							} else {
								codeVOID();
							}
						} else {
							codeVOID();
						}
					}
				}
			}
		}
	}
}
void codeED(){
	UINT8 code=_getCode();
	if (!(code&0x80)) {
		if (!(code&0x40)) {
			codeVOID();
		} else {
			if (!(code&0x20)) {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeED40();
								} else {
									codeED41();
								}
							} else {
								if (!(code&0x1)) {
									codeED42();
								} else {
									codeED43();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeED44();
								} else {
									codeED45();
								}
							} else {
								if (!(code&0x1)) {
									codeED46();
								} else {
									codeED47();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeED48();
								} else {
									codeED49();
								}
							} else {
								if (!(code&0x1)) {
									codeED4A();
								} else {
									codeED4B();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeVOID();
								} else {
									codeED4D();
								}
							} else {
								if (!(code&0x1)) {
									codeVOID();
								} else {
									codeED4F();
								}
							}
						}
					}
				} else {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeED50();
								} else {
									codeED51();
								}
							} else {
								if (!(code&0x1)) {
									codeED52();
								} else {
									codeED53();
								}
							}
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeED56();
								} else {
									codeED57();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeED58();
								} else {
									codeED59();
								}
							} else {
								if (!(code&0x1)) {
									codeED5A();
								} else {
									codeED5B();
								}
							}
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeED5E();
								} else {
									codeED5F();
								}
							}
						}
					}
				}
			} else {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeED60();
								} else {
									codeED61();
								}
							} else {
								if (!(code&0x1)) {
									codeED62();
								} else {
									codeVOID();
								}
							}
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeVOID();
								} else {
									codeED67();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeED68();
								} else {
									codeED69();
								}
							} else {
								if (!(code&0x1)) {
									codeED6A();
								} else {
									codeVOID();
								}
							}
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeVOID();
								} else {
									codeED6F();
								}
							}
						}
					}
				} else {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeED72();
								} else {
									codeED73();
								}
							}
						} else {
							codeVOID();
						}
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeED78();
								} else {
									codeED79();
								}
							} else {
								if (!(code&0x1)) {
									codeED7A();
								} else {
									codeED7B();
								}
							}
						} else {
							codeVOID();
						}
					}
				}
			}
		}
	} else {
		if (!(code&0x40)) {
			if (!(code&0x20)) {
				codeVOID();
			} else {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeEDA0();
								} else {
									codeEDA1();
								}
							} else {
								if (!(code&0x1)) {
									codeEDA2();
								} else {
									codeEDA3();
								}
							}
						} else {
							codeVOID();
						}
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeEDA8();
								} else {
									codeEDA9();
								}
							} else {
								if (!(code&0x1)) {
									codeEDAA();
								} else {
									codeEDAB();
								}
							}
						} else {
							codeVOID();
						}
					}
				} else {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeEDB0();
								} else {
									codeEDB1();
								}
							} else {
								if (!(code&0x1)) {
									codeEDB2();
								} else {
									codeEDB3();
								}
							}
						} else {
							codeVOID();
						}
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeEDB8();
								} else {
									codeEDB9();
								}
							} else {
								if (!(code&0x1)) {
									codeEDBA();
								} else {
									codeEDBB();
								}
							}
						} else {
							codeVOID();
						}
					}
				}
			}
		} else {
			codeVOID();
		}
	}
}
void codeFD(){
	UINT8 code=_getCode();
	if (!(code&0x80)) {
		if (!(code&0x40)) {
			if (!(code&0x20)) {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						codeVOID();
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeVOID();
								} else {
									codeFD09();
								}
							} else {
								codeVOID();
							}
						} else {
							codeVOID();
						}
					}
				} else {
					if (!(code&0x8)) {
						codeVOID();
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeVOID();
								} else {
									codeFD19();
								}
							} else {
								codeVOID();
							}
						} else {
							codeVOID();
						}
					}
				}
			} else {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeVOID();
								} else {
									codeFD21();
								}
							} else {
								if (!(code&0x1)) {
									codeFD22();
								} else {
									codeFD23();
								}
							}
						} else {
							codeVOID();
						}
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeVOID();
								} else {
									codeFD29();
								}
							} else {
								if (!(code&0x1)) {
									codeFD2A();
								} else {
									codeFD2B();
								}
							}
						} else {
							codeVOID();
						}
					}
				} else {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeFD34();
								} else {
									codeFD35();
								}
							} else {
								if (!(code&0x1)) {
									codeFD36();
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeVOID();
								} else {
									codeFD39();
								}
							} else {
								codeVOID();
							}
						} else {
							codeVOID();
						}
					}
				}
			}
		} else {
			if (!(code&0x20)) {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFD46();
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFD4E();
								} else {
									codeVOID();
								}
							}
						}
					}
				} else {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFD56();
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFD5E();
								} else {
									codeVOID();
								}
							}
						}
					}
				}
			} else {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFD66();
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFD6E();
								} else {
									codeVOID();
								}
							}
						}
					}
				} else {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeFD70();
								} else {
									codeFD71();
								}
							} else {
								if (!(code&0x1)) {
									codeFD72();
								} else {
									codeFD73();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeFD74();
								} else {
									codeFD75();
								}
							} else {
								if (!(code&0x1)) {
									codeVOID();
								} else {
									codeFD77();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFD7E();
								} else {
									codeVOID();
								}
							}
						}
					}
				}
			}
		}
	} else {
		if (!(code&0x40)) {
			if (!(code&0x20)) {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFD86();
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFD8E();
								} else {
									codeVOID();
								}
							}
						}
					}
				} else {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFD96();
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFD9E();
								} else {
									codeVOID();
								}
							}
						}
					}
				}
			} else {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFDA6();
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFDAE();
								} else {
									codeVOID();
								}
							}
						}
					}
				} else {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFDB6();
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFDBE();
								} else {
									codeVOID();
								}
							}
						}
					}
				}
			}
		} else {
			if (!(code&0x20)) {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						codeVOID();
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeVOID();
								} else {
									codeFDCB();
								}
							}
						} else {
							codeVOID();
						}
					}
				} else {
					codeVOID();
				}
			} else {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeVOID();
								} else {
									codeFDE1();
								}
							} else {
								if (!(code&0x1)) {
									codeVOID();
								} else {
									codeFDE3();
								}
							}
						} else {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeVOID();
								} else {
									codeFDE5();
								}
							} else {
								codeVOID();
							}
						}
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeVOID();
								} else {
									codeFDE9();
								}
							} else {
								codeVOID();
							}
						} else {
							codeVOID();
						}
					}
				} else {
					if (!(code&0x8)) {
						codeVOID();
					} else {
						if (!(code&0x4)) {
							if (!(code&0x2)) {
								if (!(code&0x1)) {
									codeVOID();
								} else {
									codeFDF9();
								}
							} else {
								codeVOID();
							}
						} else {
							codeVOID();
						}
					}
				}
			}
		}
	}
}
void codeDDCB(){
	UINT8 code;
	UINT16 i16;
	i16=regIX+getCodeIndex(code);
	code=_getCode();
	if (!(code&0x80)) {
		if (!(code&0x40)) {
			if (!(code&0x20)) {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDDCB06(i16);
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDDCB0E(i16);
								} else {
									codeVOID();
								}
							}
						}
					}
				} else {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDDCB16(i16);
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDDCB1E(i16);
								} else {
									codeVOID();
								}
							}
						}
					}
				}
			} else {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDDCB26(i16);
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDDCB2E(i16);
								} else {
									codeVOID();
								}
							}
						}
					}
				} else {
					if (!(code&0x8)) {
						codeVOID();
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDDCB3E(i16);
								} else {
									codeVOID();
								}
							}
						}
					}
				}
			}
		} else {
			if (!(code&0x20)) {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDDCB46(i16);
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDDCB4E(i16);
								} else {
									codeVOID();
								}
							}
						}
					}
				} else {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDDCB56(i16);
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDDCB5E(i16);
								} else {
									codeVOID();
								}
							}
						}
					}
				}
			} else {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDDCB66(i16);
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDDCB6E(i16);
								} else {
									codeVOID();
								}
							}
						}
					}
				} else {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDDCB76(i16);
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDDCB7E(i16);
								} else {
									codeVOID();
								}
							}
						}
					}
				}
			}
		}
	} else {
		if (!(code&0x40)) {
			if (!(code&0x20)) {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDDCB86(i16);
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDDCB8E(i16);
								} else {
									codeVOID();
								}
							}
						}
					}
				} else {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDDCB96(i16);
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDDCB9E(i16);
								} else {
									codeVOID();
								}
							}
						}
					}
				}
			} else {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDDCBA6(i16);
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDDCBAE(i16);
								} else {
									codeVOID();
								}
							}
						}
					}
				} else {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDDCBB6(i16);
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDDCBBE(i16);
								} else {
									codeVOID();
								}
							}
						}
					}
				}
			}
		} else {
			if (!(code&0x20)) {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDDCBC6(i16);
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDDCBCE(i16);
								} else {
									codeVOID();
								}
							}
						}
					}
				} else {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDDCBD6(i16);
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDDCBDE(i16);
								} else {
									codeVOID();
								}
							}
						}
					}
				}
			} else {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDDCBE6(i16);
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDDCBEE(i16);
								} else {
									codeVOID();
								}
							}
						}
					}
				} else {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDDCBF6(i16);
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeDDCBFE(i16);
								} else {
									codeVOID();
								}
							}
						}
					}
				}
			}
		}
	}
}
void codeFDCB(){
	UINT8 code;
	UINT16 i16;
	i16=regIY+getCodeIndex(code);
	code=_getCode();
	if (!(code&0x80)) {
		if (!(code&0x40)) {
			if (!(code&0x20)) {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFDCB06(i16);
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFDCB0E(i16);
								} else {
									codeVOID();
								}
							}
						}
					}
				} else {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFDCB16(i16);
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFDCB1E(i16);
								} else {
									codeVOID();
								}
							}
						}
					}
				}
			} else {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFDCB26(i16);
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFDCB2E(i16);
								} else {
									codeVOID();
								}
							}
						}
					}
				} else {
					if (!(code&0x8)) {
						codeVOID();
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFDCB3E(i16);
								} else {
									codeVOID();
								}
							}
						}
					}
				}
			}
		} else {
			if (!(code&0x20)) {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFDCB46(i16);
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFDCB4E(i16);
								} else {
									codeVOID();
								}
							}
						}
					}
				} else {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFDCB56(i16);
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFDCB5E(i16);
								} else {
									codeVOID();
								}
							}
						}
					}
				}
			} else {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFDCB66(i16);
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFDCB6E(i16);
								} else {
									codeVOID();
								}
							}
						}
					}
				} else {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFDCB76(i16);
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFDCB7E(i16);
								} else {
									codeVOID();
								}
							}
						}
					}
				}
			}
		}
	} else {
		if (!(code&0x40)) {
			if (!(code&0x20)) {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFDCB86(i16);
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFDCB8E(i16);
								} else {
									codeVOID();
								}
							}
						}
					}
				} else {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFDCB96(i16);
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFDCB9E(i16);
								} else {
									codeVOID();
								}
							}
						}
					}
				}
			} else {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFDCBA6(i16);
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFDCBAE(i16);
								} else {
									codeVOID();
								}
							}
						}
					}
				} else {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFDCBB6(i16);
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFDCBBE(i16);
								} else {
									codeVOID();
								}
							}
						}
					}
				}
			}
		} else {
			if (!(code&0x20)) {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFDCBC6(i16);
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFDCBCE(i16);
								} else {
									codeVOID();
								}
							}
						}
					}
				} else {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFDCBD6(i16);
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFDCBDE(i16);
								} else {
									codeVOID();
								}
							}
						}
					}
				}
			} else {
				if (!(code&0x10)) {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFDCBE6(i16);
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFDCBEE(i16);
								} else {
									codeVOID();
								}
							}
						}
					}
				} else {
					if (!(code&0x8)) {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFDCBF6(i16);
								} else {
									codeVOID();
								}
							}
						}
					} else {
						if (!(code&0x4)) {
							codeVOID();
						} else {
							if (!(code&0x2)) {
								codeVOID();
							} else {
								if (!(code&0x1)) {
									codeFDCBFE(i16);
								} else {
									codeVOID();
								}
							}
						}
					}
				}
			}
		}
	}
}
#endif //Z80