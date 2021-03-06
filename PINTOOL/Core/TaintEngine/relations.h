// type de relation entre TaintObjects
enum Relation 
{
    /******************************************************/
    /**** Relations de construction des objets marqu�s ****/
    /******************************************************/
    
    //! BYTESOURCE : TaintObject issu de la source suivie
    //! Source1 : offset dans l'entr�e (variable 32bits)
    BYTESOURCE = 0, 
    //! EXTRACT : Source 1 = source, Source 2 = index d'extraction (valeur 8bits)
    EXTRACT,
    //! CONCAT : concat�nation des sources (longueurs diff�rentes accept�es)
    // 1ere source = poids faible, derni�re source : poids fort
    CONCAT,

    /********************************************************/
    /**** Relations de mod�lisation des instructions x86 ****/
    /********************************************************/
    
    /** DATAXFER **/
    //! ASSIGN : Source 1 = source, m�me longueur que destination
    X_ASSIGN, 
    //! SIGN_EXTEND : Source 1 = source (longueur < � destination)
    X_SIGNEXTEND,
    //! ZERO_EXTEND : Source 1 = source (longueur < � destination)
    X_ZEROEXTEND,
    
    /**  BINARY **/   
    //! ADD : source 1 = source, source 2 = src/dest
    X_ADD,
    //! INC : source 1 = source
    X_INC,
    //! SUB : source 1 = source, source 2 = src/dest
    X_SUB, 
    //! DEC : source 1 = source
    X_DEC,
    //! NEG : source 1 = source
    X_NEG,
    //! X_MUL : voir X_IMUL
    X_MUL, 
    //! X_IMUL : source 1 = source, source 2 = src/dest.
    X_IMUL,
    // X_DIV_QUO : quotient d'une division non sign�e (src 0, 1 et 2 de meme taille)
    // Src 0 : partie haute du dividende, Src 1 : partie basse du dividende, Src 2 : totalit� du diviseur
    X_DIV_QUO, 
    // X_DIV_REM : reste d'une division non sign�e (src 0, 1 et 2 de meme taille)
    // Src 0 : partie haute du dividende, Src 1 : partie basse du dividende, Src 2 : totalit� du diviseur
    X_DIV_REM, 
    // X_IDIV_QUO : quotient d'une division sign�e (src 0, 1 et 2 de meme taille)
    // Src 0 : partie haute du dividende, Src 1 : partie basse du dividende, Src 2 : totalit� du diviseur
    X_IDIV_QUO, 
    // X_IDIV_REM : reste d'une division sign�e (src 0, 1 et 2 de meme taille)
    // Src 0 : partie haute du dividende, Src 1 : partie basse du dividende, Src 2 : totalit� du diviseur
    X_IDIV_REM,

    /** LOGICAL **/
    //! AND : source 1 = source, source 2 = src/dest 
    X_AND, 
    //! OR : source 1 = source, source 2 = src/dest
    X_OR, 
    //! XOR : source 1 = source, source 2 = src/dest
    X_XOR, 
    //! NOT : source 1 = src/dest
    X_NOT,

    /** SHIFT **/
    //! SHL : source 1 = emplacement d�plac�, source 2 = d�placement (8bits, valeur ou objet)
    // si d�placement non marqu�, il est d�j� masqu� � 0x1f ou 0x3f
    // si d�placement marqu�, le marquage sera fait dans la formule
    X_SHL, 
    //! SHR : source 1 = emplacement d�plac�, source 2 = d�placement (8bits, valeur ou objet)
    // si d�placement non marqu�, il est d�j� masqu� � 0x1f ou 0x3f
    // si d�placement marqu�, le marquage sera fait dans la formule
    X_SHR, 
    //! SAR : source 1 = emplacement d�plac�, source 2 = d�placement (8bits, valeur ou objet)
    // si d�placement non marqu�, il est d�j� masqu� � 0x1f ou 0x3f
    // si d�placement marqu�, le marquage sera fait dans la formule
    X_SAR,

    /** ROTATE **/
    //! ROR : source 1 = emplacement d�plac�, source 2 = d�placement (8bits, valeur ou objet)
    X_ROR,
    //! ROL : source 1 = emplacement d�plac�, source 2 = d�placement (8bits, valeur ou objet)
    X_ROL, 
    //! RCR : source 1 = emplacement d�plac�, source 2 = CF (1 bit) marqu� ou valeur,
    // source 3 = d�placement (8bits, valeur ou objet)
    X_RCR, 
    //! RCL : source 1 = emplacement d�plac�, source 2 = CF (1 bit) marqu� ou valeur,
    // source 3 = d�placement (8bits, valeur ou objet)
    X_RCL,

    /** BITBYTE **/
    // SETCC : donne 0 ou 1 selon que le predicat est faux ou vrai
    // src0 : predicat concern� (valeur, 32bits)
    // src1 : valeur ou marquage du flag (1 bit)
    // src2 et src3 : autres flags, si besoin
    X_SETCC,
    // COMPLEMENT_BIT : inverse le bit concern� dans la source (eq. BTC)
    // src0 : src, src1 : num�ro du bit (obj marqu� de longueur = � la source)
    // src1 est sur 16/32/64bits, 8 bits impossible. position bit marqu� sinon ce serait un EXTRACT
    X_COMPLEMENT_BIT,
    // SET_BIT : met � 1 le bit concern� dans la source (eq. BTS)
    // src0 : src, src1 : num�ro du bit (obj marqu� de longueur = � la source)
    // src1 est sur 16/32/64bits, 8 bits impossible. position bit marqu� sinon ce serait un EXTRACT
    X_SET_BIT,
    // CLEAR_BIT : met � 0 le bit concern� dans la source (eq. BTR)
    // src0 : src, src1 : num�ro du bit (obj marqu� de longueur = � la source)
    // src1 est sur 16/32/64bits, 8 bits impossible. position bit marqu� sinon ce serait un EXTRACT
    X_CLEAR_BIT,
    // BSF : Bit Scan Forward = index du LSB de la source. Source 0 = source test�e
    X_BSF,
    // BSR : Bit Scan Reverse = index du MSB de la source. Source 0 = source test�e
    X_BSR,

    /** DECIMAL **/
    // AAA/AL : marquage de AL suite � AAA. Src0 = AL (8bits), src1 = AF (1bit)
    X_AAA_AL,
    // AAA/AH : marquage de AH suite � AAA. Src0 = AL (8bits), src1 = AF (1bit)
    X_AAA_AH,
    // AAD : marquage de AL suite � AAD. Src0 = AL (8bits), src1 = AH (8bits), src2 = base utilis�e (valeur - 8bits)
    X_AAD,
    // AAM/AL : marquage de AL suite � AAM. Src0 = marquage AL (8bits), src1 = base utilis�e (8bits)
    X_AAM_AL,
    // AAM/AH : marquage de AH suite � AAM. Src0 = marquage AH (8bits), src1 = base utilis�e (8bits)
    X_AAM_AH,
    // AAS/AL : marquage de AL suite � AAS. Src0 = AH (8bits), src1 = AL (8bits), src2 = AF (1bit)
    X_AAS_AL,
    // AAS/AH : marquage de AH suite � AAS. Src0 = AH (8bits), src1 = AL (8bits), src2 = AF (1bit)
    X_AAS_AH,
    // DAA_1ST : relation calculant AL en fonction de la premi�re condition de DAA. Src0 = AL (8bits), Src1 = AF (1bit)
    X_DAA_1ST,
    // DAA_2ND : relation calculant AL en fonction de la seconde condition de DAA
    // Src0 = AL avant DAA (8 bits), Src1 = CF (1bit), src2 = AL apres 1ere condition de DAA (8bits)
    X_DAA_2ND,
    // DAS_1ST : relation calculant AL en fonction de la premi�re condition de DAS. Src0 = AL (8bits), Src1 = AF (1bit)
    X_DAS_1ST,
    // DAS_2ND : relation calculant AL en fonction de la seconde condition de DAS
    // Src0 = AL avant DAS (8 bits), Src1 = CF (1bit), src2 = AL apres 1ere condition de DAS (8bits)
    X_DAS_2ND,

    /** FLAGOP  **/
    // SALC : source0 : carryFlag (1bit), resultat sur 8 bits (affect� � AL)
    X_SALC,

    /*******************************************************************/
    /**** Relations de modelisation des effets de bords (flags) x86 ****/
    /*******************************************************************/
    
    // LSB : bit de poids faible. source 0 = source
    F_LSB,
    // MSB : bit de poids fort. source 0 = source. Equivaut au Sign Flag 
    F_MSB,

    /* CARRY_FLAG */
    // CARRY_ADD : Source0 : src/dest, source1 : src
    F_CARRY_ADD,
    // CARRY_SUB : Source0 : src/dest, source1 : src
    F_CARRY_SUB,
    // CARRY_NEG : Source0 : src (vrai ssi source non nulle)
    F_CARRY_NEG,
    // CARRY_MUL : Source0 : resultat. Si partie haute du resultat nulle, CF mis � 0 
    F_CARRY_MUL, 
    // CARRY_IMUL : Source0 : resultat; si resultat = sign_extend partie basse, alors CF mis � 0
    F_CARRY_IMUL,  
    // CARRY_SHL : denier bit eject� (cas ou la source est marqu� sinon traitement direct par extract)
    // Source0 : source, source1 : depl (marqu� - 8bits, sera masqu� � 0x1f ou 0x3f dans la formule)
    F_CARRY_SHL,
    // CARRY_SHR : denier bit eject� (cas ou la source est marqu� sinon traitement direct par extract)
    // Source0 : source, source1 : depl (marqu� - 8bits, sera masqu� � 0x1f ou 0x3f dans la formule)
    F_CARRY_SHR,
    // CARRY_SAR : denier bit eject� (cas ou la source est marqu� sinon traitement direct par extract)
    // Source0 : source, source1 : depl (marqu� - 8bits, sera masqu� � 0x1f ou 0x3f dans la formule)
    // IDENTIQUE A CARRY_SHR car le deplacement est masqu�, donc au maximal ce sera le MSB de la source
    // qui sera �ject�
    F_CARRY_SAR = F_CARRY_SHR, 
    // CARRY_RCL : denier bit eject� (cas ou la source est marqu� sinon traitement direct par extract)
    // Source0 : source, source1: depl (marqu� - 8bits, sera masqu� � 0x1f ou 0x3f dans la formule)
    F_CARRY_RCL,
    // CARRY_RCR : denier bit eject� (cas ou la source est marqu� sinon traitement direct par extract)
    // Source0 : source, source1: depl (marqu� - 8bits, sera masqu� � 0x1f ou 0x3f dans la formule)
    F_CARRY_RCR, 
    // CARRY_BITBYTE : extraction du bit 'b' de la source, lorsque la position
    // du bit est marqu�. !! source0 et source1 sont de la meme taille
    // Source0 : source, source1 : n� bit (marqu�). Sera ajust� modulo 16/32/64
    F_CARRY_BITBYTE,

    /** PARITY_FLAG **/
    // PARITY. source 0 = resultat. seuls les 8 bits faibles seront consid�r�s
    F_PARITY,

    /** ZERO_FLAG **/
    // F_IS_NULL : 1 si source0 est nulle, 0 sinon
    F_IS_NULL,
    // F_ARE_EQUAL : 1 si source0 et source1 sont �gales, 0 sinon
    F_ARE_EQUAL,
    // CMPXCHG 8B et 16B : ZF � 1 si les deux op�randes sont �gales
    // Srcs 0 et 1 = m�moire  (partie haute et partie basse), objets de 32 ou 64bits
    // Srcs 2 et 3 = registre (partie haute et partie basse), objets de 32 ou 64bits
    F_CMPXCHG_8B16B,

    /** OVERFLOW_FLAG **/
    // OF_ADD : Src0 : src/dest, src1 : src, src2 : result
    F_OVERFLOW_ADD,
    // OF_SUB : Src0 : src/dest, src1 : src, src2 : result
    F_OVERFLOW_SUB, 
    // OF_INC : Src0 : src/dest
    F_OVERFLOW_INC,
    // OF_DEC : Src0 : src/dest
    F_OVERFLOW_DEC,
    F_OVERFLOW_NEG = F_OVERFLOW_DEC, // formule identique NEG et DEC
    
    // OF_SHL (ssi depl == 1). 1 si signe change entre src et resultat. 
    // Src0 = resultat, src1 = src
    F_OVERFLOW_SHL, 
    // OF_SHRD (ssi depl == 1). 1 si signe avant et apres change 
    // donc si MSB src != LSB Bit Pattern.
    // Source0 = concatenation bitPattern(partie haute) et source shift�e
    F_OVERFLOW_SHRD,
    // OF_ROL (ssi depl == 1). MSB(DEST) XOR CF : cf manuel Intel
    // Source0 = resultat, source1 = CF apres rotation (marqu�, 1bit)
    F_OVERFLOW_ROL,
    // OF_ROR (ssi depl == 1). MSB(DEST) XOR ((MSB-1) DEST) : cf manuel Intel
    // Source0 = resultat
    F_OVERFLOW_ROR,

    // AUXILIARY FLAG
    // AUXILIARY_ADD : Source0 : src/dest, source1 : src
    F_AUXILIARY_ADD,
    // AUXILIARY_NEG : source0 = source
    F_AUXILIARY_NEG,
    // AUXILIARY_SUB : Source0 : src/dest, source1 : src
    F_AUXILIARY_SUB,
    // AUXILIARY_INC : source0 = source
    F_AUXILIARY_INC,
    // AUXILIARY_DEC : source0 = source
    F_AUXILIARY_DEC,

    /** DECIMAL **/
    // AAA : marquage Carry/auxiliary suite � AAA . Identique pour AAS et DAA (pour AF)
    // src0 = AL (8bits), src1 = AF (1 bit)
    F_AAA,
    // DAA et DAS (pour CF) : src0 = AL avant DAA (8 bits), src1 = CF (1bit)
    F_CARRY_DAA_DAS,

    RELATION_LAST
};

const static std::string relationStrings[RELATION_LAST] = 
{
    // TaintObject issu de la source suivie
    "BYTESOURCE", 

    // construction d'objets par extraction 
    // ou concat�nation d'autres objets
    "EXTRACT",
    "CONCAT",

    /**** Relations de modelisation des instructions x86 ****/

    // DATAXFER
    "X_ASSIGN", "X_SIGNEXTEND", "X_ZEROEXTEND",
    
    // BINARY
    "X_ADD", "X_INC", "X_SUB", "X_DEC", "X_NEG",
    "X_MUL", "X_IMUL",
    // division non sign�e avec quotient et reste
    "X_DIV_QUO", "X_DIV_REM", 
    // division sign�e avec quotient et reste
    "X_IDIV_QUO", "X_IDIV_REM",

    // LOGICAL
    "X_AND", "X_OR", "X_XOR", "X_NOT",

    // SHIFT
    "X_SHL", "X_SHR", "X_SAR",

    // ROTATE
    "X_ROR", "X_ROL", "X_RCR", "X_RCL",

    // BIT_BYTE
    "X_SETCC", "X_COMPLEMENT_BIT", "X_SET_BIT", "X_CLEAR_BIT", "X_BSF", "X_BSR",

    // DECIMAL
    "X_AAA_AL", "X_AAA_AH", "X_AAD", "X_AAM_AL", "X_AAM_AH", "X_AAS_AL", "X_AAS_AH",
    "X_DAA_1ST", "X_DAA_2ND", "X_DAS_1ST", "X_DAS_2ND",
    
    // FLAGOP
    "X_SALC",

    /**** Relations de modelisation des effets de bords (flags) x86 ****/
    
    "F_LSB", "F_MSB",   
    
    // CARRY_FLAG
    "F_CARRY_ADD", "F_CARRY_SUB", "F_CARRY_NEG", "F_CARRY_MUL", "F_IMUL",
    "F_CARRY_SHL", "F_CARRY_SHR/SAR",
    "F_CARRY_RCL", "F_CARRY_RCR",
    "F_CARRY_BITBYTE",

    // PARITY FLAG
    "F_PARITY",

    // ZERO FLAG
    "F_IS_NULL",
    "F_ARE_EQUAL",
    "F_CMPXCHG_8B16B",

    // OVERFLOW FLAG
    "F_OVERFLOW_ADD", "F_OVERFLOW_SUB",
    "F_OVERFLOW_INC", "F_OVERFLOW_DEC/NEG",
    "F_OVERFLOW_SHL", "F_OVERFLOW_SHRD",
    "F_OVERFLOW_ROL", "F_OVERFLOW_ROR",
    
    // AUXILIARY FLAG
    "F_AUXILIARY_ADD",
    "F_AUXILIARY_NEG",
    "F_AUXILIARY_SUB",
    "F_AUXILIARY_INC",
    "F_AUXILIARY_DEC",

    // DECIMAL 
    "F_AAA", "F_CARRY_DAA_DAS",
};