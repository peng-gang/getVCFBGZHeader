# getVCFBGZHeader
Get VCF file header from a vcf.bgz file.

## Build
Before build the code, make sure [HTSlib](http://www.htslib.org/download/) is installed first.

g++ -lhts -o getHeader main.c

## Run
./getHeader input.vcf.gzg outputHeader.vcf

