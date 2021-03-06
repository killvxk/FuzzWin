// SIMULATE

#if TARGET_IA32
template<UINT32 lenDest, UINT32 lenEA> 
void MISC::sLEA(THREADID tid, REG regDest, ADDRINT insAddress)
{
    TaintManager_Thread *pTmgrTls = getTmgrInTls(tid);
    
    // r�cup�ration de l'objet pr�alablement calcul� et stock� par cGetKindOfEA, si existant
    // sinon d�marquer la destination
    if (!pTmgrTls->isEffectiveAddressTainted()) pTmgrTls->unTaintRegister<32>(regDest);
    else
    {
        _LOGTAINT(tid, insAddress, "LEA");

        TaintDwordPtr eaPtr = pTmgrTls->getTaintEffectiveAddress();
    
        // Boucle de 0 � (lenEA >> 3)  : extraction octet i de l'objet marqu�
        // et affectation � octet i du registre de destination (sauf si lenDest < leaEA : on arrete avant)
        // octets de (lenEA >> 3) � (lenDest >> 3) mis � z�ro si besoin
    
        REGINDEX regDestIndex    = getRegIndex(regDest);
        UINT32   regPart         = 0;
        // dernier octet qui sera marqu� dans le registre de destination
        UINT32   lastTaintedByte = (lenEA < lenDest) ? (lenEA >> 3) : (lenDest >> 3); 

        // marquage destination
        do
        {
            pTmgrTls->updateTaintRegisterPart(regDestIndex, regPart, std::make_shared<TaintByte>
                (EXTRACT,
                ObjectSource(eaPtr),
                ObjectSource(8, regPart)));
            ++regPart;
        } while (regPart < lastTaintedByte);

        // d�marquage octets forts (si lenDest > lenEA car zeroextend de l'EA)
        while (regPart < (lenDest >> 3))
        {
            pTmgrTls->unTaintRegisterPart(regDestIndex, regPart);
            ++regPart;
        }
    }
    pTmgrTls->clearTaintEffectiveAddress();
} // sLEA(32bits)

#else

template<UINT32 lenDest, UINT32 lenEA> 
void MISC::sLEA(THREADID tid, REG regDest, ADDRINT insAddress)
{
    TaintManager_Thread *pTmgrTls = getTmgrInTls(tid);
    
    // r�cup�ration de l'objet pr�alablement calcul� et stock� par cGetKindOfEA, si existant
    // sinon d�marquer la destination
    if (!pTmgrTls->isEffectiveAddressTainted()) pTmgrTls->unTaintRegister<64>(regDest);
    else
    {
        TaintQwordPtr eaPtr = pTmgrTls->getTaintEffectiveAddress();
    
        _LOGTAINT(tid, insAddress, "LEA");

        // Boucle de 0 � (lenEA >> 3)  : extraction octet i de l'objet marqu�
        // et affectation � octet i du registre de destination (sauf si lenDest < leaEA : on arrete avant)
        // octets de (lenEA >> 3) � (lenDest >> 3) mis � z�ro si besoin
    
        REGINDEX regDestIndex    = getRegIndex(regDest);
        UINT32   regPart         = 0;
        // dernier octet qui sera marqu� dans le registre de destination
        UINT32   lastTaintedByte = (lenEA < lenDest) ? (lenEA >> 3) : (lenDest >> 3); 

        // marquage destination
        do
        {
            pTmgrTls->updateTaintRegisterPart(regDestIndex, regPart, std::make_shared<TaintByte>
                (EXTRACT,
                ObjectSource(eaPtr),
                ObjectSource(8, regPart)));
            ++regPart;
        } while (regPart < lastTaintedByte);

        // d�marquage octets forts (si lenDest > lenEA car zeroextend de l'EA)
        while (regPart < (lenDest >> 3))
        {
            pTmgrTls->unTaintRegisterPart(regDestIndex, regPart);
            ++regPart;
        }
    }
    pTmgrTls->clearTaintEffectiveAddress();
} // sLEA(64bits)

#endif