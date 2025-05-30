// original code from cabd_memory.c of libmspack
// the only changes made to lzxd.c and system.h are the #includes from <> to ""
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lzxd.c"

struct mem_buf {
  void *data;
  size_t length;
};

struct mem_file {
  unsigned char *data;
  size_t length, posn;
};

static void *mem_alloc(struct mspack_system *this, size_t bytes) {
  return malloc(bytes);
}

static void mem_free(void *buffer) {
  free(buffer);
}

static void mem_copy(void *src, void *dest, size_t bytes) {
  memcpy(dest, src, bytes);
}

static void mem_msg(struct mem_file *file, unsigned char *format, ...) {
}

static struct mem_file *mem_open(struct mspack_system *this,
				 struct mem_buf *fn, int mode)
{
  struct mem_file *fh;
  if (!fn || !fn->data || !fn->length) return NULL;
  if ((fh = mem_alloc(this, sizeof(struct mem_file)))) {
    fh->data   = fn->data;
    fh->length = fn->length;
    fh->posn   = (mode == MSPACK_SYS_OPEN_APPEND) ? fn->length : 0;
  }
  return fh;
}

static void mem_close(struct mem_file *fh) {
  if (fh) mem_free(fh);
}

static int mem_read(struct mem_file *fh, void *buffer, int bytes) {
  int todo;
  if (!fh) return -1;
  todo = fh->length - fh->posn;
  if (todo > bytes) todo = bytes;
  if (todo > 0) mem_copy(&fh->data[fh->posn], buffer, (size_t) todo);
  fh->posn += todo; return todo;
}

static int mem_write(struct mem_file *fh, void *buffer, int bytes) {
  int todo;
  if (!fh) return -1;
  todo = fh->length - fh->posn;
  if (todo > bytes) todo = bytes;
  if (todo > 0) mem_copy(buffer, &fh->data[fh->posn], (size_t) todo);
  fh->posn += todo; return todo;
}

static int mem_seek(struct mem_file *fh, off_t offset, int mode) {
  if (!fh) return 1;
  switch (mode) {
  case MSPACK_SYS_SEEK_START: break;
  case MSPACK_SYS_SEEK_CUR:   offset += (off_t) fh->posn; break;
  case MSPACK_SYS_SEEK_END:   offset += (off_t) fh->length; break;
  default: return 1;
  }
  if ((offset < 0) || (offset > (off_t) fh->length)) return 1;
  fh->posn = (size_t) offset;
  return 0;
}

static off_t mem_tell(struct mem_file *fh) {
  return (fh) ? (off_t) fh->posn : -1;
}

static struct mspack_system mem_system = {
  (struct mspack_file * (*)()) &mem_open,
  (void (*)())  &mem_close,
  (int (*)())   &mem_read, 
  (int (*)())   &mem_write,
  (int (*)())   &mem_seek, 
  (off_t (*)()) &mem_tell,
  (void (*)())  &mem_msg,
  &mem_alloc,
  &mem_free,
  &mem_copy,
  NULL
};

int unmslzx(unsigned char *in, int insz, unsigned char *out, int outsz, int window_bits, int interval) {
    struct lzxd_stream *state = NULL;
    struct mspack_file *fd = NULL,
                       *fdo = NULL;
    struct mem_buf source = { in, insz };
    struct mem_buf dest   = { out, outsz };
    int     ret    = -1;

    fd = mem_system.open(&mem_system, (unsigned char *)&source, 0);
    if(!fd) goto quit;
    fdo = mem_system.open(&mem_system, (unsigned char *)&dest, 0);
    if(!fdo) goto quit;
    state = lzxd_init(&mem_system, fd, fdo, window_bits, interval, 4096, 0);
    if(!state) goto quit;
    //if(lzxd_decompress(state, outsz) != MSPACK_ERR_OK) goto quit;
    lzxd_decompress(state, outsz);
    ret = mem_system.tell(fdo);
quit:
    if(fd) mem_system.close(fd);
    if(state) lzxd_free(state);
    return(ret);
}
