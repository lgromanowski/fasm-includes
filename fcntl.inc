include 'struct.inc' ; STRUCT.INC comes from FASMW package (Flat Assembler, package for windows)

; FMODE_EXEC is 0x20
; FMODE_NONOTIFY is 0x4000000
; These cannot be used by userspace O_* until internal and external open
; flags are split.
; -Eric Paris

; When introducing new O_* bits, please check its uniqueness in fcntl_init().

O_ACCMODE      = 00000003
O_RDONLY       = 00000000
O_WRONLY       = 00000001
O_RDWR         = 00000002
O_CREAT        = 00000100        ; not fcntl
O_EXCL         = 00000200        ; not fcntl
O_NOCTTY       = 00000400        ; not fcntl
O_TRUNC        = 00001000        ; not fcntl
O_APPEND       = 00002000
O_NONBLOCK     = 00004000
O_DSYNC        = 00010000        ; used to be O_SYNC, see below
FASYNC         = 00020000        ; fcntl, for BSD compatibility
O_DIRECT       = 00040000        ; direct disk access hint
O_LARGEFILE    = 00100000
O_DIRECTORY    = 00200000        ; must be a directory
O_NOFOLLOW     = 00400000        ; don't follow links
O_NOATIME      = 01000000
O_CLOEXEC      = 02000000        ; set close_on_exec

; Before Linux 2.6.33 only O_DSYNC semantics were implemented, but using
; the O_SYNC flag.  We continue to use the existing numerical value
; for O_DSYNC semantics now, but using the correct symbolic name for it.
; This new value is used to request true Posix O_SYNC semantics.  It is
; defined in this strange way to make sure applications compiled against
; new headers get at least O_DSYNC semantics on older kernels.
;
; This has the nice side-effect that we can simply test for O_DSYNC
; wherever we do not care if O_DSYNC or O_SYNC is used.
;
; Note: __O_SYNC must never be used directly.

__O_SYNC       = 04000000
O_SYNC         = (__O_SYNC or O_DSYNC)
O_PATH         = 010000000
__O_TMPFILE    = 020000000

; a horrid kludge trying to make sure that this will fail on old kernels
O_TMPFILE       = (__O_TMPFILE  or  O_DIRECTORY)
O_TMPFILE_MASK  = (__O_TMPFILE  or  O_DIRECTORY  or  O_CREAT)

O_NDELAY        = O_NONBLOCK

F_DUPFD         = 0       ; dup
F_GETFD         = 1       ; get close_on_exec
F_SETFD         = 2       ; set/clear close_on_exec
F_GETFL         = 3       ; get file->f_flags
F_SETFL         = 4       ; set file->f_flags
F_GETLK         = 5
F_SETLK         = 6
F_SETLKW        = 7
F_SETOWN        = 8       ; for sockets.
F_GETOWN        = 9       ; for sockets.
F_SETSIG        = 10      ; for sockets.
F_GETSIG        = 11      ; for sockets.

F_GETLK64       = 12      ;  using 'struct flock64'
F_SETLK64       = 13
F_SETLKW64      = 14
F_SETOWN_EX     = 15
F_GETOWN_EX     = 16
F_GETOWNER_UIDS = 17


; Open File Description Locks
;
; Usually record locks held by a process are released on *any* close and are
; not inherited across a fork().
;
; These cmd values will set locks that conflict with process-associated
; record  locks, but are "owned" by the open file description, not the
; process. This means that they are inherited across fork() like BSD (flock)
; locks, and they are only released automatically when the last reference to
; the the open file against which they were acquired is put.
;
F_OFD_GETLK     = 36
F_OFD_SETLK     = 37
F_OFD_SETLKW    = 38

F_OWNER_TID    = 0
F_OWNER_PID    = 1
F_OWNER_PGRP   = 2

struct f_owner_ex
  type    dd ?
  pid     dd ? ; __kernel_pid_t
ends

; for F_[GET or SET]FL
FD_CLOEXEC      = 1       ; actually anything with low bit set goes

; for posix fcntl() and lockf()
F_RDLCK         = 0
F_WRLCK         = 1
F_UNLCK         = 2

; for old implementation of bsd flock ()
F_EXLCK         = 4       ; or 3
F_SHLCK         = 8       ; or 4

; operations for bsd flock(), also used by the kernel implementation
LOCK_SH         = 1       ; shared lock
LOCK_EX         = 2       ; exclusive lock
LOCK_NB         = 4       ; or'd with one of the above to prevent blocking
LOCK_UN         = 8       ; remove lock

LOCK_MAND       = 32      ; This is a mandatory flock ...
LOCK_READ       = 64      ; which allows concurrent read operations
LOCK_WRITE      = 128     ; which allows concurrent write operations
LOCK_RW         = 192     ; which allows concurrent read & write ops

F_LINUX_SPECIFIC_BASE   = 1024

struct flock
  l_type      dw ?
  l_whence    dw ?
  l_start     dd ? ; __kernel_off_t
  l_len       dd ? ; __kernel_off_t
  l_pid       dd ? ; __kernel_pid_t
  ; __ARCH_FLOCK_PAD ???
ends

struct flock64
  l_type      dw ?
  l_whence    dw ?
  l_start     dq ? ; __kernel_loff_t
  l_len       dq ? ; __kernel_loff_t
  l_pid       dd ? ; __kernel_pid_t
  ; __ARCH_FLOCK64_PAD ???
ends
