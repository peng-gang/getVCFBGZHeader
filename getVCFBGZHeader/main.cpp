//
//  main.cpp
//  getVCFBGZHeader
//
//  Created by Gang Peng on 4/24/20.
//  Copyright © 2020 Gang Peng. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <htslib/hts.h>
#include <htslib/vcf.h>
#include <htslib/kstring.h>
#include <htslib/kseq.h>

void error(const char *format, ...){
    va_list ap;
    va_start(ap, format);
    vfprintf(stderr, format, ap);
    va_end(ap);
    if (strrchr(format, '\n') == NULL) fputc('\n', stderr);
    exit(-1);
}

int main(int argc, const char * argv[]) {
    htsFile *fp    = hts_open(argv[1],"rb");
    if (!fp) error("Failed to open \"%s\" : %s", argv[1], strerror(errno));
    bcf_hdr_t *hdr = bcf_hdr_read(fp);
    if (!hdr) error("bcf_hdr_read : %s", strerror(errno));
    bcf1_t *rec    = bcf_init1();
    if (!rec) error("bcf_init1 : %s", strerror(errno));
    
    // get header file
    htsFile *out   = hts_open(argv[2],"w");
    if (!out) {
        error("Couldn't open \"%s\" : %s\n", argv[2], strerror(errno));
    }
    
    bcf_hdr_t *hdr_out = bcf_hdr_dup(hdr);
    if ( bcf_hdr_write(out, hdr_out)!=0 ) error("Failed to write to %s\n", argv[2]);
    
    bcf_hdr_destroy(hdr_out);
    int ret;
    if ( (ret=hts_close(out)) )
    {
        fprintf(stderr,"hts_close(%s): non-zero status %d\n", argv[2], ret);
        exit(ret);
    }
     
    
    bcf_destroy1(rec);
    bcf_hdr_destroy(hdr);
    if ( (ret=hts_close(fp)) )
    {
        fprintf(stderr,"hts_close(%s): non-zero status %d\n", argv[1], ret);
        exit(ret);
    }
    return 0;
}
