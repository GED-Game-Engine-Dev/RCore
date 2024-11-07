#include <GED/Core/Camera.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <stdint.h>

static void Process(
    GED_Core_Camera_t* _this,
    ae2f_struct ae2f_Bmp_cSrc* dest, 
    uint32_t background_asRGB,
    uint8_t tdidx,
    uint8_t tdlen,
    size_t _this_len
) {
    ae2f_errint_t code;
    uint32_t 
        left, right,
        gwidth = ae2f_Bmp_Idx_XLeft(dest->rIdxer),
        pwidth = (gwidth / tdlen);

    right = left = pwidth * tdidx;
    right += pwidth;
    if(right > gwidth) right = gwidth;

    for(size_t i = 0; i < _this_len; i+=sizeof(struct GED_Core_Camera_El)) {
        ae2f_struct GED_Core_Camera_El _element;
        if((code = ae2f_ds_Alloc_cOwn_Read(
            _this,
            i,
            &_element,
            sizeof(GED_Core_Camera_El))) != ae2f_errGlob_OK
        ) goto DONE;

        if(!_element.Source.Addr) continue;

        if((code = ae2f_Bmp_cSrc_Copy_Partial(
                    dest, &_element.Source, &_element.SourceLinked, 
                    left, 0, right, 
                    ae2f_Bmp_Idx_YLeft(dest->rIdxer)
                )
            ) != ae2f_errGlob_OK) // Real
        goto DONE;
    }

    DONE:
    return;
}

static void ProcessFill(
    ae2f_struct ae2f_Bmp_cSrc* dest, 
    uint32_t background_asRGB,
    uint8_t tdidx,
    uint8_t tdlen
) {
    uint32_t 
        left, right,
        gwidth = ae2f_Bmp_Idx_XLeft(dest->rIdxer),
        pwidth = (gwidth / tdlen);

    right = left = pwidth * tdidx;
    right += pwidth;
    if(right > gwidth) right = gwidth;

    ae2f_Bmp_cSrc_Fill_Partial(
        dest,
        background_asRGB,
        left,
        0,
        right,
        ae2f_Bmp_Idx_YLeft(dest->rIdxer)
    );
}

#include <stdlib.h>
struct buff {
    std::thread* a;
    inline buff(uint8_t tdcount) { a = (std::thread*)calloc(tdcount, sizeof(std::thread)); }
    inline ~buff() { if(a) free(a); }
};

ae2f_extern ae2f_SHAREDEXPORT
ae2f_errint_t GED_Core_Camera_Buff_Threaded(
    GED_Core_Camera_t* _this,
    ae2f_struct ae2f_Bmp_cSrc* dest,
    uint32_t background_asRGB,
    uint8_t tdcount
) {
    buff tds(tdcount);
    if(!tds.a) {
        return ae2f_errGlob_ALLOC_FAILED;
    }

    size_t a; ae2f_errint_t code = ae2f_errGlob_OK;
    if((code = ae2f_ds_Alloc_cOwn_getSize(_this, &a, 0)) != ae2f_ds_Alloc_Err_NCOPIED)
    goto DONE;
    switch (background_asRGB)
    {
    default: {
        for(uint8_t i = 0; i < tdcount; i++) {
            new(tds.a + i) std::thread(ProcessFill, dest, background_asRGB, i, tdcount);
        }

        ProcessFill(dest, background_asRGB, tdcount, tdcount);

        for(uint8_t i = 0; i < tdcount; i++) {
            tds.a[i].join();
            tds.a[i].~thread();
        }

    } break;
    case (uint32_t)-1:
        break;
    }
    
    for(uint8_t i = 0; i < tdcount; i++) {
        new(tds.a + i) std::thread(Process, _this, dest, background_asRGB, i, tdcount, a);
    }

    // Process(_this, dest, background_asRGB, tdcount, tdcount, a);

    for(uint8_t i = 0; i < tdcount; i++) {
        tds.a[i].join();
        tds.a[i].~thread();
    }

    DONE:
    return code;
}