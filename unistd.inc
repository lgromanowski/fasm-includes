stdin         = 0
stdout        = 1
stderr        = 3
STDIN         = 0
STDOUT        = 1
STDERR        = 3
STDIN_FILENO  = stdin
STDOUT_FILENO = stdout
STDERR_FILENO = stderr

; Values for the second argument to access. These may be OR'd together.
R_OK = 4  ; Test for read permission.
W_OK = 2  ; Test for write permission.
X_OK = 1  ; Test for execute permission.
F_OK = 0  ; Test for existence.

SEEK_SET  = 0 ; Seek from beginning of file.
SEEK_CUR  = 1 ; Seek from current position.
SEEK_END  = 2 ; Seek from end of file.
SEEK_DATA = 3 ; Seek to next data.
SEEK_HOLE = 4 ; Seek to next hole.

F_ULOCK = 0 ; Unlock a previously locked region.
F_LOCK  = 1 ; Lock a region for exclusive use.
F_TLOCK = 2 ; Test and lock a region for exclusive use.
F_TEST  = 3 ; Test a region for other processes locks.
