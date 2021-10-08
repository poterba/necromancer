
#pragma once

#include <stdint.h>
#include <sys/types.h>

typedef uint32_t mach_port_right_t;

typedef unsigned int mach_msg_bits_t;
typedef unsigned int mach_msg_size_t;
typedef unsigned int mach_msg_id_t;

typedef unsigned int mach_port_name_t;
typedef mach_port_name_t mach_port_t;

#define MACH_PORT_RIGHT_RECEIVE ((mach_port_right_t)1)
#define MACH_PORT_NULL 0 /* intentional loose typing */

typedef struct
{
    mach_msg_bits_t msgh_bits;
    mach_msg_size_t msgh_size;
    mach_port_t msgh_remote_port;
    mach_port_t msgh_local_port;
    mach_msg_size_t msgh_reserved;
    mach_msg_id_t msgh_id;
} mach_msg_header_t;

#define MACH_MSG_TYPE_COPY_SEND 19 /* Must hold send rights */
#define MACH_MSG_TYPE_MAKE_SEND 20 /* Must hold receive rights */

#define MACH_SEND_MSG 0x00000001

#define MACH_MSGH_BITS(remote, local) ((remote) | ((local) << 8))

typedef int64_t __darwin_blkcnt_t;
typedef int32_t __darwin_blksize_t;
typedef uint16_t __darwin_nlink_t; /* link count */

struct __darwin_timespec
{
    int tv_sec;
    int tv_nsec;
};

typedef uint32_t __darwin_dev_t;
typedef uint16_t __darwin_mode_t;
typedef uint64_t __darwin_off_t;

typedef struct fsid
{
    int32_t val[2];
} __darwin_fsid_t; /* file system id type */

struct proc_regioninfo
{
    uint32_t pri_protection;
    uint32_t pri_max_protection;
    uint32_t pri_inheritance;
    uint32_t pri_flags; /* shared, external pager, is submap */
    uint64_t pri_offset;
    uint32_t pri_behavior;
    uint32_t pri_user_wired_count;
    uint32_t pri_user_tag;
    uint32_t pri_pages_resident;
    uint32_t pri_pages_shared_now_private;
    uint32_t pri_pages_swapped_out;
    uint32_t pri_pages_dirtied;
    uint32_t pri_ref_count;
    uint32_t pri_shadow_depth;
    uint32_t pri_share_mode;
    uint32_t pri_private_pages_resident;
    uint32_t pri_shared_pages_resident;
    uint32_t pri_obj_id;
    uint32_t pri_depth;
    uint64_t pri_address;
    uint64_t pri_size;
};

struct vinfo_stat
{
    uint32_t vst_dev;          /* [XSI] ID of device containing file */
    uint16_t vst_mode;         /* [XSI] Mode of file (see below) */
    uint16_t vst_nlink;        /* [XSI] Number of hard links */
    uint64_t vst_ino;          /* [XSI] File serial number */
    uid_t vst_uid;             /* [XSI] User ID of the file */
    gid_t vst_gid;             /* [XSI] Group ID of the file */
    int64_t vst_atime;         /* [XSI] Time of last access */
    int64_t vst_atimensec;     /* nsec of last access */
    int64_t vst_mtime;         /* [XSI] Last data modification time */
    int64_t vst_mtimensec;     /* last data modification nsec */
    int64_t vst_ctime;         /* [XSI] Time of last status change */
    int64_t vst_ctimensec;     /* nsec of last status change */
    int64_t vst_birthtime;     /*  File creation time(birth)  */
    int64_t vst_birthtimensec; /* nsec of File creation time */
    __darwin_off_t vst_size;   /* [XSI] file size, in bytes */
    int64_t vst_blocks;        /* [XSI] blocks allocated for file */
    int32_t vst_blksize;       /* [XSI] optimal blocksize for I/O */
    uint32_t vst_flags;        /* user defined flags for file */
    uint32_t vst_gen;          /* file generation number */
    uint32_t vst_rdev;         /* [XSI] Device ID */
    int64_t vst_qspare[2];     /* RESERVED: DO NOT USE! */
};

struct vnode_info
{
    struct vinfo_stat vi_stat;
    int vi_type;
    int vi_pad;
    __darwin_fsid_t vi_fsid;
};

struct vnode_info_path
{
    struct vnode_info vip_vi;
    char vip_path[1024]; /* tail end of it  */
};

struct proc_regionwithpathinfo
{
    struct proc_regioninfo prp_prinfo;
    struct vnode_info_path prp_vip;
};

#define VNIOCATTACH _IOWR('F', 0, struct vn_ioctl) /* attach file */
#define VNIOCDETACH _IOWR('F', 1, struct vn_ioctl)

typedef unsigned int __32bit_ptr;

struct vn_ioctl
{
    __32bit_ptr vn_file; /* pathname of file to mount */
    int vn_size;         /* (returned) size of disk */
    int vn_control;      /* this is vncontrol_t, but we need to ensure 32 bit size */
};

typedef enum
{
    vncontrol_readwrite_io_e = 0
} vncontrol_t;

#define MNT_RDONLY 0x00000001 /* read only filesystem */
#define MNT_UPDATE 0x00010000 /* not a real mount, just an update */

struct __darwin_timezone
{
    int tz_minuteswest; /* minutes west of Greenwich */
    int tz_dsttime;     /* type of dst correction */
};

struct hfs_mount_args
{
    __32bit_ptr fspec;
    uid_t hfs_uid;
    gid_t hfs_gid;
    __darwin_mode_t hfs_mask;
    uint32_t hfs_encoding;
    struct __darwin_timezone hfs_timezone;
    int flags;
    int journal_tbuffer_size;
    int journal_flags;
    int journal_disable;
};

#define LOG_WARNING 4

#define SHELLCODE_ADDR 0x80000400
#define ZFREEHOOK_ADDR (offsets->ZFREE - 1)
#define ZFREEHOOKER_ADDR 0x80000600

#define SB_EVALUATEHOOK_ADDR (offsets->SB_EVALUATE - 1)
#define SB_EVALUATEHOOKER_ADDR 0x80000700

#define CTL_KERN 1      /* "high kernel": proc, limits */
#define KERN_PROC 14    /* struct: process entries */
#define KERN_PROC_ALL 0 /* everything */

#define SM_SHARED 4

#define RTLD_DEFAULT ((__32bit_ptr)-2) /* Use default search algorithm. */
