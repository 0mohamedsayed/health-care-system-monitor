
#ifndef UTILS_H_
#define UTILS_H_

#define SetBit(Var,BitNum) (Var|=(1<<BitNum))
#define ClrBit(Var,BitNum) (Var&=~(1<<BitNum))
#define TogBit(Var,BitNum) (Var^=(1<<BitNum))
#define GetBit(Var,BitNum) ((Var>>BitNum)&1)




#endif /* UTILS_H_ */
