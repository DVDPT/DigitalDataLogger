#pragma once
#ifdef _DEBUG
#define FTD2XXX_CHECK_STATUS(exp) {if(exp!=FT_OK){printf("%s:%d:%s(): status(0x%x) != FT_OK\n",__FILE__, __LINE__, __FUNCTION__,exp);exit(1);}else{;}};
#else 
#define FTD2XXX_CHECK_STATUS(exp) 
#endif