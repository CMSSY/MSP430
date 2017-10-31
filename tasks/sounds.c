#include "sounds.h"

//FRESULT f_mount(uint8_t, FATFS*);                                      /* Mount/Unmount a logical drive */
//FRESULT f_open(FIL *, const TCHAR *, uint8_t);                         /* Open or create a file */
//FRESULT f_read(FIL *, void*, uint16_t, uint16_t*);                          /* Read data from a file */
//FRESULT f_lseek(FIL *, uint32_t);                                      /* Move file pointer of a file object */
//FRESULT f_close (FIL*);                                             /* Close an open file object */
//FRESULT f_opendir (DIR*, const TCHAR*);                             /* Open an existing directory */
//FRESULT f_readdir (DIR*, FILINFO*);                                 /* Read a directory item */
//FRESULT f_stat (const TCHAR*, FILINFO*);                            /* Get file status */
//
//#if !_FS_READONLY
//FRESULT f_write(FIL *, const void*, uint16_t, uint16_t*);                   /* Write data to a file */
//FRESULT f_getfree (const TCHAR*, uint32_t*, FATFS**);                  /* Get number of free clusters on the drive */
//FRESULT f_truncate (FIL*);                                          /* Truncate file */
//FRESULT f_sync (FIL*);                                              /* Flush cached data of a writing file */
//FRESULT f_unlink (const TCHAR*);                                    /* Delete an existing file or directory */
//FRESULT f_mkdir (const TCHAR*);                                     /* Create a new directory */
//FRESULT f_chmod(const TCHAR *, uint8_t, uint8_t);                         /* Change attriburte of the file/dir */
//FRESULT f_utime (const TCHAR*, const FILINFO*);                     /* Change timestamp of the file/dir */
//FRESULT f_rename (const TCHAR*, const TCHAR*);                      /* Rename/Move a file or directory */
//
//
//FRESULT f_open (
//    FIL *fp,                                                                /* Pointer to the blank file object */
//    const TCHAR *path,                                                      /* Pointer to the file name */
//    uint8_t mode                                                               /* Access mode and file open mode flags */
//    )

DRESULT playSoundEffect(const char* p_file)
{
//	FIL *fp = 0;
	uint8_t buffer[256];
	uint16_t bytesRead = 0;

	DRESULT dresult = disk_read(0, //Physical drive number (0)
		buffer,    //Pointer to the user buffer
		0,           //First LBA of this buffer operation
		100);      //The number of blocks being requested

//	FRESULT ret = f_open(fp, p_file, FA_READ);

//	if (!fp) { return ret; }

//	FRESULT f_read (
//	    FIL *fp,                                                                /* Pointer to the file object */
//	    void *buff,                                                             /* Pointer to data buffer */
//	    uint16_t btr,                                                               /* Number of bytes to read */
//	    uint16_t *br                                                                /* Pointer to number of bytes read */
//	    )
//	f_read(fp, buffer, 100, &bytesRead);

	return RES_OK;
}
