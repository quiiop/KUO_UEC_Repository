/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the w64 mingw-runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */
#ifndef _KS_
#define _KS_

#if __GNUC__ >= 3
#pragma GCC system_header
#endif /* #if __GNUC__ >= 3 */

#ifndef __MINGW_EXTENSION
#if defined(__GNUC__) || defined(__GNUG__)
#define __MINGW_EXTENSION __extension__
#else /* #if defined(__GNUC__) || defined(__GNUG__) */
#define __MINGW_EXTENSION
#endif /* #if defined(__GNUC__) || defined(__GNUG__) */
#endif /* #ifndef __MINGW_EXTENSION */

#ifdef __TCS__
#define _KS_NO_ANONYMOUS_STRUCTURES_ 1
#endif /* #ifdef __TCS__ */

#ifdef  _KS_NO_ANONYMOUS_STRUCTURES_
#define _KS_ANON_STRUCT(X)          struct X
#else /* #ifdef  _KS_NO_ANONYMOUS_STRUCTURES_ */
#define _KS_ANON_STRUCT(X)  __MINGW_EXTENSION struct
#endif /* #ifdef  _KS_NO_ANONYMOUS_STRUCTURES_ */

#ifndef _NTRTL_
#ifndef DEFINE_GUIDEX
#define DEFINE_GUIDEX(name) EXTERN_C const CDECL GUID name
#endif /* #ifndef DEFINE_GUIDEX */
#ifndef STATICGUIDOF
#define STATICGUIDOF(guid) STATIC_##guid
#endif /* #ifndef STATICGUIDOF */
#endif /* #ifndef _NTRTL_ */

#ifndef SIZEOF_ARRAY
#define SIZEOF_ARRAY(ar) (sizeof(ar)/sizeof((ar)[0]))
#endif /* #ifndef SIZEOF_ARRAY */

#define DEFINE_GUIDSTRUCT(g,n) DEFINE_GUIDEX(n)
#define DEFINE_GUIDNAMED(n) n

#define STATIC_GUID_NULL                        \
    0x00000000L,0x0000,0x0000,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00

DEFINE_GUIDSTRUCT("00000000-0000-0000-0000-000000000000", GUID_NULL);
#define GUID_NULL DEFINE_GUIDNAMED(GUID_NULL)

#define IOCTL_KS_PROPERTY CTL_CODE(FILE_DEVICE_KS,0x000,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_KS_ENABLE_EVENT CTL_CODE(FILE_DEVICE_KS,0x001,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_KS_DISABLE_EVENT CTL_CODE(FILE_DEVICE_KS,0x002,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_KS_METHOD CTL_CODE(FILE_DEVICE_KS,0x003,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_KS_WRITE_STREAM CTL_CODE(FILE_DEVICE_KS,0x004,METHOD_NEITHER,FILE_WRITE_ACCESS)
#define IOCTL_KS_READ_STREAM CTL_CODE(FILE_DEVICE_KS,0x005,METHOD_NEITHER,FILE_READ_ACCESS)
#define IOCTL_KS_RESET_STATE CTL_CODE(FILE_DEVICE_KS,0x006,METHOD_NEITHER,FILE_ANY_ACCESS)

typedef enum {
    KSRESET_BEGIN,
    KSRESET_END
} KSRESET;

typedef enum {
    KSSTATE_STOP,
    KSSTATE_ACQUIRE,
    KSSTATE_PAUSE,
    KSSTATE_RUN
} KSSTATE, *PKSSTATE;

#define KSPRIORITY_LOW      0x00000001
#define KSPRIORITY_NORMAL   0x40000000
#define KSPRIORITY_HIGH     0x80000000
#define KSPRIORITY_EXCLUSIVE    0xFFFFFFFF

typedef struct {
    ULONG PriorityClass;
    ULONG PrioritySubClass;
} KSPRIORITY, *PKSPRIORITY;

typedef struct {
    __MINGW_EXTENSION union {
        _KS_ANON_STRUCT(_IDENTIFIER) {
            GUID Set;
            ULONG Id;
            ULONG Flags;
        };
        LONGLONG Alignment;
    };
} KSIDENTIFIER, *PKSIDENTIFIER;

typedef KSIDENTIFIER KSPROPERTY, *PKSPROPERTY, KSMETHOD, *PKSMETHOD, KSEVENT, *PKSEVENT;

#define KSMETHOD_TYPE_NONE      0x00000000
#define KSMETHOD_TYPE_READ      0x00000001
#define KSMETHOD_TYPE_WRITE     0x00000002
#define KSMETHOD_TYPE_MODIFY        0x00000003
#define KSMETHOD_TYPE_SOURCE        0x00000004

#define KSMETHOD_TYPE_SEND      0x00000001
#define KSMETHOD_TYPE_SETSUPPORT    0x00000100
#define KSMETHOD_TYPE_BASICSUPPORT  0x00000200

#define KSMETHOD_TYPE_TOPOLOGY      0x10000000

#define KSPROPERTY_TYPE_GET     0x00000001
#define KSPROPERTY_TYPE_SET     0x00000002
#define KSPROPERTY_TYPE_SETSUPPORT  0x00000100
#define KSPROPERTY_TYPE_BASICSUPPORT    0x00000200
#define KSPROPERTY_TYPE_RELATIONS   0x00000400
#define KSPROPERTY_TYPE_SERIALIZESET    0x00000800
#define KSPROPERTY_TYPE_UNSERIALIZESET  0x00001000
#define KSPROPERTY_TYPE_SERIALIZERAW    0x00002000
#define KSPROPERTY_TYPE_UNSERIALIZERAW  0x00004000
#define KSPROPERTY_TYPE_SERIALIZESIZE   0x00008000
#define KSPROPERTY_TYPE_DEFAULTVALUES   0x00010000

#define KSPROPERTY_TYPE_TOPOLOGY    0x10000000

typedef struct {
    KSPROPERTY Property;
    ULONG NodeId;
    ULONG Reserved;
} KSP_NODE, *PKSP_NODE;

typedef struct {
    KSMETHOD Method;
    ULONG NodeId;
    ULONG Reserved;
} KSM_NODE, *PKSM_NODE;

typedef struct {
    KSEVENT Event;
    ULONG NodeId;
    ULONG Reserved;
} KSE_NODE, *PKSE_NODE;

#define STATIC_KSPROPTYPESETID_General                  \
    0x97E99BA0L,0xBDEA,0x11CF,0xA5,0xD6,0x28,0xDB,0x04,0xC1,0x00,0x00
DEFINE_GUIDSTRUCT("97E99BA0-BDEA-11CF-A5D6-28DB04C10000", KSPROPTYPESETID_General);
#define KSPROPTYPESETID_General DEFINE_GUIDNAMED(KSPROPTYPESETID_General)

typedef struct {
    ULONG Size;
    ULONG Count;
} KSMULTIPLE_ITEM, *PKSMULTIPLE_ITEM;

typedef struct {
    ULONG AccessFlags;
    ULONG DescriptionSize;
    KSIDENTIFIER PropTypeSet;
    ULONG MembersListCount;
    ULONG Reserved;
} KSPROPERTY_DESCRIPTION, *PKSPROPERTY_DESCRIPTION;

#define KSPROPERTY_MEMBER_RANGES        0x00000001
#define KSPROPERTY_MEMBER_STEPPEDRANGES     0x00000002
#define KSPROPERTY_MEMBER_VALUES        0x00000003

#define KSPROPERTY_MEMBER_FLAG_DEFAULT      0x00000001
#define KSPROPERTY_MEMBER_FLAG_BASICSUPPORT_MULTICHANNEL 0x00000002
#define KSPROPERTY_MEMBER_FLAG_BASICSUPPORT_UNIFORM 0x00000004

typedef struct {
    ULONG MembersFlags;
    ULONG MembersSize;
    ULONG MembersCount;
    ULONG Flags;
} KSPROPERTY_MEMBERSHEADER, *PKSPROPERTY_MEMBERSHEADER;

typedef union {
    _KS_ANON_STRUCT(_SIGNED) {
        LONG SignedMinimum;
        LONG SignedMaximum;
    };
    _KS_ANON_STRUCT(_UNSIGNED) {
        ULONG UnsignedMinimum;
        ULONG UnsignedMaximum;
    };
} KSPROPERTY_BOUNDS_LONG, *PKSPROPERTY_BOUNDS_LONG;

typedef union {
    _KS_ANON_STRUCT(_SIGNED64) {
        LONGLONG SignedMinimum;
        LONGLONG SignedMaximum;
    };
    _KS_ANON_STRUCT(_UNSIGNED64) {
        DWORDLONG UnsignedMinimum;
        DWORDLONG UnsignedMaximum;
    };
} KSPROPERTY_BOUNDS_LONGLONG, *PKSPROPERTY_BOUNDS_LONGLONG;

typedef struct {
    ULONG SteppingDelta;
    ULONG Reserved;
    KSPROPERTY_BOUNDS_LONG Bounds;
} KSPROPERTY_STEPPING_LONG, *PKSPROPERTY_STEPPING_LONG;

typedef struct {
    DWORDLONG SteppingDelta;
    KSPROPERTY_BOUNDS_LONGLONG Bounds;
} KSPROPERTY_STEPPING_LONGLONG, *PKSPROPERTY_STEPPING_LONGLONG;

#if defined(_NTDDK_)
typedef struct _KSDEVICE_DESCRIPTOR KSDEVICE_DESCRIPTOR, *PKSDEVICE_DESCRIPTOR;
typedef struct _KSDEVICE_DISPATCH KSDEVICE_DISPATCH, *PKSDEVICE_DISPATCH;
typedef struct _KSDEVICE KSDEVICE, *PKSDEVICE;
typedef struct _KSFILTERFACTORY KSFILTERFACTORY, *PKSFILTERFACTORY;
typedef struct _KSFILTER_DESCRIPTOR KSFILTER_DESCRIPTOR, *PKSFILTER_DESCRIPTOR;
typedef struct _KSFILTER_DISPATCH KSFILTER_DISPATCH, *PKSFILTER_DISPATCH;
typedef struct _KSFILTER KSFILTER, *PKSFILTER;
typedef struct _KSPIN_DESCRIPTOR_EX KSPIN_DESCRIPTOR_EX, *PKSPIN_DESCRIPTOR_EX;
typedef struct _KSPIN_DISPATCH KSPIN_DISPATCH, *PKSPIN_DISPATCH;
typedef struct _KSCLOCK_DISPATCH KSCLOCK_DISPATCH, *PKSCLOCK_DISPATCH;
typedef struct _KSALLOCATOR_DISPATCH KSALLOCATOR_DISPATCH, *PKSALLOCATOR_DISPATCH;
typedef struct _KSPIN KSPIN, *PKSPIN;
typedef struct _KSNODE_DESCRIPTOR KSNODE_DESCRIPTOR, *PKSNODE_DESCRIPTOR;
typedef struct _KSSTREAM_POINTER_OFFSET KSSTREAM_POINTER_OFFSET, *PKSSTREAM_POINTER_OFFSET;
typedef struct _KSSTREAM_POINTER KSSTREAM_POINTER, *PKSSTREAM_POINTER;
typedef struct _KSMAPPING KSMAPPING, *PKSMAPPING;
typedef struct _KSPROCESSPIN KSPROCESSPIN, *PKSPROCESSPIN;
typedef struct _KSPROCESSPIN_INDEXENTRY KSPROCESSPIN_INDEXENTRY, *PKSPROCESSPIN_INDEXENTRY;
#endif /* #if defined(_NTDDK_) */

typedef PVOID PKSWORKER;


typedef struct {
    ULONG NotificationType;
    __MINGW_EXTENSION union {
        struct {
            HANDLE Event;
            ULONG_PTR Reserved[2];
        } EventHandle;
        struct {
            HANDLE Semaphore;
            ULONG Reserved;
            LONG Adjustment;
        } SemaphoreHandle;
#if defined(_NTDDK_)
        struct {
            PVOID Event;
            KPRIORITY Increment;
            ULONG_PTR Reserved;
        } EventObject;
        struct {
            PVOID Semaphore;
            KPRIORITY Increment;
            LONG Adjustment;
        } SemaphoreObject;
        struct {
            PKDPC Dpc;
            ULONG ReferenceCount;
            ULONG_PTR Reserved;
        } Dpc;
        struct {
            PWORK_QUEUE_ITEM WorkQueueItem;
            WORK_QUEUE_TYPE WorkQueueType;
            ULONG_PTR Reserved;
        } WorkItem;
        struct {
            PWORK_QUEUE_ITEM WorkQueueItem;
            PKSWORKER KsWorkerObject;
            ULONG_PTR Reserved;
        } KsWorkItem;
#endif /* #if defined(_NTDDK_) */
        struct {
            PVOID Unused;
            LONG_PTR Alignment[2];
        } Alignment;
    };
} KSEVENTDATA, *PKSEVENTDATA;

#define KSEVENTF_EVENT_HANDLE       0x00000001
#define KSEVENTF_SEMAPHORE_HANDLE   0x00000002
#if defined(_NTDDK_)
#define KSEVENTF_EVENT_OBJECT       0x00000004
#define KSEVENTF_SEMAPHORE_OBJECT   0x00000008
#define KSEVENTF_DPC            0x00000010
#define KSEVENTF_WORKITEM       0x00000020
#define KSEVENTF_KSWORKITEM     0x00000080
#endif /* #if defined(_NTDDK_) */

#define KSEVENT_TYPE_ENABLE     0x00000001
#define KSEVENT_TYPE_ONESHOT        0x00000002
#define KSEVENT_TYPE_ENABLEBUFFERED 0x00000004
#define KSEVENT_TYPE_SETSUPPORT     0x00000100
#define KSEVENT_TYPE_BASICSUPPORT   0x00000200
#define KSEVENT_TYPE_QUERYBUFFER    0x00000400

#define KSEVENT_TYPE_TOPOLOGY       0x10000000

typedef struct {
    KSEVENT Event;
    PKSEVENTDATA EventData;
    PVOID Reserved;
} KSQUERYBUFFER, *PKSQUERYBUFFER;

typedef struct {
    ULONG Size;
    ULONG Flags;
    __MINGW_EXTENSION union {
        HANDLE ObjectHandle;
        PVOID ObjectPointer;
    };
    PVOID Reserved;
    KSEVENT Event;
    KSEVENTDATA EventData;
} KSRELATIVEEVENT;

#define KSRELATIVEEVENT_FLAG_HANDLE 0x00000001
#define KSRELATIVEEVENT_FLAG_POINTER    0x00000002

typedef struct {
    KSEVENTDATA EventData;
    LONGLONG MarkTime;
} KSEVENT_TIME_MARK, *PKSEVENT_TIME_MARK;

typedef struct {
    KSEVENTDATA EventData;
    LONGLONG TimeBase;
    LONGLONG Interval;
} KSEVENT_TIME_INTERVAL, *PKSEVENT_TIME_INTERVAL;

typedef struct {
    LONGLONG TimeBase;
    LONGLONG Interval;
} KSINTERVAL, *PKSINTERVAL;

#define STATIC_KSPROPSETID_General                  \
    0x1464EDA5L,0x6A8F,0x11D1,0x9A,0xA7,0x00,0xA0,0xC9,0x22,0x31,0x96
DEFINE_GUIDSTRUCT("1464EDA5-6A8F-11D1-9AA7-00A0C9223196", KSPROPSETID_General);
#define KSPROPSETID_General DEFINE_GUIDNAMED(KSPROPSETID_General)

typedef enum {
    KSPROPERTY_GENERAL_COMPONENTID
} KSPROPERTY_GENERAL;

typedef struct {
    GUID Manufacturer;
    GUID Product;
    GUID Component;
    GUID Name;
    ULONG Version;
    ULONG Revision;
} KSCOMPONENTID, *PKSCOMPONENTID;

#define DEFINE_KSPROPERTY_ITEM_GENERAL_COMPONENTID(Handler)     \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_GENERAL_COMPONENTID,     \
                (Handler),              \
                sizeof(KSPROPERTY),         \
                sizeof(KSCOMPONENTID),          \
                NULL, NULL, 0, NULL, NULL, 0)

#define STATIC_KSMETHODSETID_StreamIo   \
    0x65D003CAL,0x1523,0x11D2,0xB2,0x7A,0x00,0xA0,0xC9,0x22,0x31,0x96
DEFINE_GUIDSTRUCT("65D003CA-1523-11D2-B27A-00A0C9223196", KSMETHODSETID_StreamIo);
#define KSMETHODSETID_StreamIo DEFINE_GUIDNAMED(KSMETHODSETID_StreamIo)

typedef enum {
    KSMETHOD_STREAMIO_READ,
    KSMETHOD_STREAMIO_WRITE
} KSMETHOD_STREAMIO;

#define DEFINE_KSMETHOD_ITEM_STREAMIO_READ(Handler)         \
    DEFINE_KSMETHOD_ITEM(                       \
                KSMETHOD_STREAMIO_READ,         \
                KSMETHOD_TYPE_WRITE,            \
                (Handler),              \
                sizeof(KSMETHOD),           \
                0,                  \
                NULL)

#define DEFINE_KSMETHOD_ITEM_STREAMIO_WRITE(Handler)            \
    DEFINE_KSMETHOD_ITEM(                       \
                KSMETHOD_STREAMIO_WRITE,        \
                KSMETHOD_TYPE_READ,         \
                (Handler),              \
                sizeof(KSMETHOD),           \
                0,                  \
                NULL)

#define STATIC_KSPROPSETID_MediaSeeking                 \
    0xEE904F0CL,0xD09B,0x11D0,0xAB,0xE9,0x00,0xA0,0xC9,0x22,0x31,0x96
DEFINE_GUIDSTRUCT("EE904F0C-D09B-11D0-ABE9-00A0C9223196", KSPROPSETID_MediaSeeking);
#define KSPROPSETID_MediaSeeking DEFINE_GUIDNAMED(KSPROPSETID_MediaSeeking)

typedef enum {
    KSPROPERTY_MEDIASEEKING_CAPABILITIES,
    KSPROPERTY_MEDIASEEKING_FORMATS,
    KSPROPERTY_MEDIASEEKING_TIMEFORMAT,
    KSPROPERTY_MEDIASEEKING_POSITION,
    KSPROPERTY_MEDIASEEKING_STOPPOSITION,
    KSPROPERTY_MEDIASEEKING_POSITIONS,
    KSPROPERTY_MEDIASEEKING_DURATION,
    KSPROPERTY_MEDIASEEKING_AVAILABLE,
    KSPROPERTY_MEDIASEEKING_PREROLL,
    KSPROPERTY_MEDIASEEKING_CONVERTTIMEFORMAT
} KSPROPERTY_MEDIASEEKING;

typedef enum {
    KS_SEEKING_NoPositioning,
    KS_SEEKING_AbsolutePositioning,
    KS_SEEKING_RelativePositioning,
    KS_SEEKING_IncrementalPositioning,
    KS_SEEKING_PositioningBitsMask = 0x3,
    KS_SEEKING_SeekToKeyFrame,
    KS_SEEKING_ReturnTime = 0x8
} KS_SEEKING_FLAGS;

typedef enum {
    KS_SEEKING_CanSeekAbsolute = 0x1,
    KS_SEEKING_CanSeekForwards = 0x2,
    KS_SEEKING_CanSeekBackwards = 0x4,
    KS_SEEKING_CanGetCurrentPos = 0x8,
    KS_SEEKING_CanGetStopPos = 0x10,
    KS_SEEKING_CanGetDuration = 0x20,
    KS_SEEKING_CanPlayBackwards = 0x40
} KS_SEEKING_CAPABILITIES;

typedef struct {
    LONGLONG Current;
    LONGLONG Stop;
    KS_SEEKING_FLAGS CurrentFlags;
    KS_SEEKING_FLAGS StopFlags;
} KSPROPERTY_POSITIONS, *PKSPROPERTY_POSITIONS;

typedef struct {
    LONGLONG Earliest;
    LONGLONG Latest;
} KSPROPERTY_MEDIAAVAILABLE, *PKSPROPERTY_MEDIAAVAILABLE;

typedef struct {
    KSPROPERTY Property;
    GUID SourceFormat;
    GUID TargetFormat;
    LONGLONG Time;
} KSP_TIMEFORMAT, *PKSP_TIMEFORMAT;

#define DEFINE_KSPROPERTY_ITEM_MEDIASEEKING_CAPABILITIES(Handler)   \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_MEDIASEEKING_CAPABILITIES,   \
                (Handler),              \
                sizeof(KSPROPERTY),         \
                sizeof(KS_SEEKING_CAPABILITIES),    \
                NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_MEDIASEEKING_FORMATS(Handler)        \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_MEDIASEEKING_FORMATS,    \
                (Handler),              \
                sizeof(KSPROPERTY),         \
                0,                  \
                NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_MEDIASEEKING_TIMEFORMAT(GetHandler,SetHandler) \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_MEDIASEEKING_TIMEFORMAT, \
                (GetHandler),               \
                sizeof(KSPROPERTY),         \
                sizeof(GUID),               \
                (SetHandler),               \
                NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_MEDIASEEKING_POSITION(Handler)       \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_MEDIASEEKING_POSITION,   \
                (Handler),              \
                sizeof(KSPROPERTY),         \
                sizeof(LONGLONG),           \
                NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_MEDIASEEKING_STOPPOSITION(Handler)   \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_MEDIASEEKING_STOPPOSITION,   \
                (Handler),              \
                sizeof(KSPROPERTY),         \
                sizeof(LONGLONG),           \
                NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_MEDIASEEKING_POSITIONS(Handler)      \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_MEDIASEEKING_POSITIONS,  \
                NULL,                   \
                sizeof(KSPROPERTY),         \
                sizeof(KSPROPERTY_POSITIONS),       \
                (Handler),              \
                NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_MEDIASEEKING_DURATION(Handler)       \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_MEDIASEEKING_DURATION,   \
                (Handler),              \
                sizeof(KSPROPERTY),         \
                sizeof(LONGLONG),           \
                NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_MEDIASEEKING_AVAILABLE(Handler)      \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_MEDIASEEKING_AVAILABLE,  \
                (Handler),              \
                sizeof(KSPROPERTY),         \
                sizeof(KSPROPERTY_MEDIAAVAILABLE),  \
                NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_MEDIASEEKING_PREROLL(Handler)        \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_MEDIASEEKING_PREROLL,    \
                (Handler),              \
                sizeof(KSPROPERTY),         \
                sizeof(LONGLONG),           \
                NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_MEDIASEEKING_CONVERTTIMEFORMAT(Handler)  \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_MEDIASEEKING_CONVERTTIMEFORMAT, \
                (Handler),              \
                sizeof(KSP_TIMEFORMAT),         \
                sizeof(LONGLONG),           \
                NULL, NULL, 0, NULL, NULL, 0)

#define STATIC_KSPROPSETID_Topology                 \
    0x720D4AC0L,0x7533,0x11D0,0xA5,0xD6,0x28,0xDB,0x04,0xC1,0x00,0x00
DEFINE_GUIDSTRUCT("720D4AC0-7533-11D0-A5D6-28DB04C10000", KSPROPSETID_Topology);
#define KSPROPSETID_Topology DEFINE_GUIDNAMED(KSPROPSETID_Topology)

typedef enum {
    KSPROPERTY_TOPOLOGY_CATEGORIES,
    KSPROPERTY_TOPOLOGY_NODES,
    KSPROPERTY_TOPOLOGY_CONNECTIONS,
    KSPROPERTY_TOPOLOGY_NAME
} KSPROPERTY_TOPOLOGY;

#define DEFINE_KSPROPERTY_ITEM_TOPOLOGY_CATEGORIES(Handler)     \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_TOPOLOGY_CATEGORIES,     \
                (Handler),              \
                sizeof(KSPROPERTY),         \
                0,                  \
                NULL, NULL, 0,NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_TOPOLOGY_NODES(Handler)          \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_TOPOLOGY_NODES,      \
                (Handler),              \
                sizeof(KSPROPERTY),         \
                0,                  \
                NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_TOPOLOGY_CONNECTIONS(Handler)        \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_TOPOLOGY_CONNECTIONS,    \
                (Handler),              \
                sizeof(KSPROPERTY),         \
                0,                  \
                NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_TOPOLOGY_NAME(Handler)           \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_TOPOLOGY_NAME,       \
                (Handler),              \
                sizeof(KSP_NODE),           \
                0,                  \
                NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_TOPOLOGYSET(TopologySet,Handler)      \
DEFINE_KSPROPERTY_TABLE(TopologySet) {                  \
    DEFINE_KSPROPERTY_ITEM_TOPOLOGY_CATEGORIES(Handler),        \
    DEFINE_KSPROPERTY_ITEM_TOPOLOGY_NODES(Handler),         \
    DEFINE_KSPROPERTY_ITEM_TOPOLOGY_CONNECTIONS(Handler),       \
    DEFINE_KSPROPERTY_ITEM_TOPOLOGY_NAME(Handler)           \
}

#define STATIC_KSCATEGORY_BRIDGE                    \
    0x085AFF00L,0x62CE,0x11CF,0xA5,0xD6,0x28,0xDB,0x04,0xC1,0x00,0x00
DEFINE_GUIDSTRUCT("085AFF00-62CE-11CF-A5D6-28DB04C10000", KSCATEGORY_BRIDGE);
#define KSCATEGORY_BRIDGE DEFINE_GUIDNAMED(KSCATEGORY_BRIDGE)

#define STATIC_KSCATEGORY_CAPTURE                   \
    0x65E8773DL,0x8F56,0x11D0,0xA3,0xB9,0x00,0xA0,0xC9,0x22,0x31,0x96
DEFINE_GUIDSTRUCT("65E8773D-8F56-11D0-A3B9-00A0C9223196", KSCATEGORY_CAPTURE);
#define KSCATEGORY_CAPTURE DEFINE_GUIDNAMED(KSCATEGORY_CAPTURE)

#define STATIC_KSCATEGORY_RENDER                    \
    0x65E8773EL,0x8F56,0x11D0,0xA3,0xB9,0x00,0xA0,0xC9,0x22,0x31,0x96
DEFINE_GUIDSTRUCT("65E8773E-8F56-11D0-A3B9-00A0C9223196", KSCATEGORY_RENDER);
#define KSCATEGORY_RENDER DEFINE_GUIDNAMED(KSCATEGORY_RENDER)

#define STATIC_KSCATEGORY_MIXER                     \
    0xAD809C00L,0x7B88,0x11D0,0xA5,0xD6,0x28,0xDB,0x04,0xC1,0x00,0x00
DEFINE_GUIDSTRUCT("AD809C00-7B88-11D0-A5D6-28DB04C10000", KSCATEGORY_MIXER);
#define KSCATEGORY_MIXER DEFINE_GUIDNAMED(KSCATEGORY_MIXER)

#define STATIC_KSCATEGORY_SPLITTER                  \
    0x0A4252A0L,0x7E70,0x11D0,0xA5,0xD6,0x28,0xDB,0x04,0xC1,0x00,0x00
DEFINE_GUIDSTRUCT("0A4252A0-7E70-11D0-A5D6-28DB04C10000", KSCATEGORY_SPLITTER);
#define KSCATEGORY_SPLITTER DEFINE_GUIDNAMED(KSCATEGORY_SPLITTER)

#define STATIC_KSCATEGORY_DATACOMPRESSOR                \
    0x1E84C900L,0x7E70,0x11D0,0xA5,0xD6,0x28,0xDB,0x04,0xC1,0x00,0x00
DEFINE_GUIDSTRUCT("1E84C900-7E70-11D0-A5D6-28DB04C10000", KSCATEGORY_DATACOMPRESSOR);
#define KSCATEGORY_DATACOMPRESSOR DEFINE_GUIDNAMED(KSCATEGORY_DATACOMPRESSOR)

#define STATIC_KSCATEGORY_DATADECOMPRESSOR              \
    0x2721AE20L,0x7E70,0x11D0,0xA5,0xD6,0x28,0xDB,0x04,0xC1,0x00,0x00
DEFINE_GUIDSTRUCT("2721AE20-7E70-11D0-A5D6-28DB04C10000", KSCATEGORY_DATADECOMPRESSOR);
#define KSCATEGORY_DATADECOMPRESSOR DEFINE_GUIDNAMED(KSCATEGORY_DATADECOMPRESSOR)

#define STATIC_KSCATEGORY_DATATRANSFORM                 \
    0x2EB07EA0L,0x7E70,0x11D0,0xA5,0xD6,0x28,0xDB,0x04,0xC1,0x00,0x00
DEFINE_GUIDSTRUCT("2EB07EA0-7E70-11D0-A5D6-28DB04C10000", KSCATEGORY_DATATRANSFORM);
#define KSCATEGORY_DATATRANSFORM DEFINE_GUIDNAMED(KSCATEGORY_DATATRANSFORM)

#define STATIC_KSCATEGORY_COMMUNICATIONSTRANSFORM           \
    0xCF1DDA2CL,0x9743,0x11D0,0xA3,0xEE,0x00,0xA0,0xC9,0x22,0x31,0x96
DEFINE_GUIDSTRUCT("CF1DDA2C-9743-11D0-A3EE-00A0C9223196", KSCATEGORY_COMMUNICATIONSTRANSFORM);
#define KSCATEGORY_COMMUNICATIONSTRANSFORM DEFINE_GUIDNAMED(KSCATEGORY_COMMUNICATIONSTRANSFORM)

#define STATIC_KSCATEGORY_INTERFACETRANSFORM                \
    0xCF1DDA2DL,0x9743,0x11D0,0xA3,0xEE,0x00,0xA0,0xC9,0x22,0x31,0x96
DEFINE_GUIDSTRUCT("CF1DDA2D-9743-11D0-A3EE-00A0C9223196", KSCATEGORY_INTERFACETRANSFORM);
#define KSCATEGORY_INTERFACETRANSFORM DEFINE_GUIDNAMED(KSCATEGORY_INTERFACETRANSFORM)

#define STATIC_KSCATEGORY_MEDIUMTRANSFORM               \
    0xCF1DDA2EL,0x9743,0x11D0,0xA3,0xEE,0x00,0xA0,0xC9,0x22,0x31,0x96
DEFINE_GUIDSTRUCT("CF1DDA2E-9743-11D0-A3EE-00A0C9223196", KSCATEGORY_MEDIUMTRANSFORM);
#define KSCATEGORY_MEDIUMTRANSFORM DEFINE_GUIDNAMED(KSCATEGORY_MEDIUMTRANSFORM)

#define STATIC_KSCATEGORY_FILESYSTEM                    \
    0x760FED5EL,0x9357,0x11D0,0xA3,0xCC,0x00,0xA0,0xC9,0x22,0x31,0x96
DEFINE_GUIDSTRUCT("760FED5E-9357-11D0-A3CC-00A0C9223196", KSCATEGORY_FILESYSTEM);
#define KSCATEGORY_FILESYSTEM DEFINE_GUIDNAMED(KSCATEGORY_FILESYSTEM)

#define STATIC_KSCATEGORY_CLOCK                     \
    0x53172480L,0x4791,0x11D0,0xA5,0xD6,0x28,0xDB,0x04,0xC1,0x00,0x00
DEFINE_GUIDSTRUCT("53172480-4791-11D0-A5D6-28DB04C10000", KSCATEGORY_CLOCK);
#define KSCATEGORY_CLOCK DEFINE_GUIDNAMED(KSCATEGORY_CLOCK)

#define STATIC_KSCATEGORY_PROXY                     \
    0x97EBAACAL,0x95BD,0x11D0,0xA3,0xEA,0x00,0xA0,0xC9,0x22,0x31,0x96
DEFINE_GUIDSTRUCT("97EBAACA-95BD-11D0-A3EA-00A0C9223196", KSCATEGORY_PROXY);
#define KSCATEGORY_PROXY DEFINE_GUIDNAMED(KSCATEGORY_PROXY)

#define STATIC_KSCATEGORY_QUALITY                   \
    0x97EBAACBL,0x95BD,0x11D0,0xA3,0xEA,0x00,0xA0,0xC9,0x22,0x31,0x96
DEFINE_GUIDSTRUCT("97EBAACB-95BD-11D0-A3EA-00A0C9223196", KSCATEGORY_QUALITY);
#define KSCATEGORY_QUALITY DEFINE_GUIDNAMED(KSCATEGORY_QUALITY)

typedef struct {
    ULONG FromNode;
    ULONG FromNodePin;
    ULONG ToNode;
    ULONG ToNodePin;
} KSTOPOLOGY_CONNECTION, *PKSTOPOLOGY_CONNECTION;

typedef struct {
    ULONG CategoriesCount;
    const GUID *Categories;
    ULONG TopologyNodesCount;
    const GUID *TopologyNodes;
    ULONG TopologyConnectionsCount;
    const KSTOPOLOGY_CONNECTION *TopologyConnections;
    const GUID *TopologyNodesNames;
    ULONG Reserved;
} KSTOPOLOGY, *PKSTOPOLOGY;

#define KSFILTER_NODE   ((ULONG)-1)
#define KSALL_NODES ((ULONG)-1)

typedef struct {
    ULONG CreateFlags;
    ULONG Node;
} KSNODE_CREATE, *PKSNODE_CREATE;

#define STATIC_KSTIME_FORMAT_NONE   STATIC_GUID_NULL
#define KSTIME_FORMAT_NONE      GUID_NULL

#define STATIC_KSTIME_FORMAT_FRAME                  \
    0x7b785570L,0x8c82,0x11cf,0xbc,0x0c,0x00,0xaa,0x00,0xac,0x74,0xf6
DEFINE_GUIDSTRUCT("7b785570-8c82-11cf-bc0c-00aa00ac74f6", KSTIME_FORMAT_FRAME);
#define KSTIME_FORMAT_FRAME DEFINE_GUIDNAMED(KSTIME_FORMAT_FRAME)

#define STATIC_KSTIME_FORMAT_BYTE                   \
    0x7b785571L,0x8c82,0x11cf,0xbc,0x0c,0x00,0xaa,0x00,0xac,0x74,0xf6
DEFINE_GUIDSTRUCT("7b785571-8c82-11cf-bc0c-00aa00ac74f6", KSTIME_FORMAT_BYTE);
#define KSTIME_FORMAT_BYTE DEFINE_GUIDNAMED(KSTIME_FORMAT_BYTE)

#define STATIC_KSTIME_FORMAT_SAMPLE                 \
    0x7b785572L,0x8c82,0x11cf,0xbc,0x0c,0x00,0xaa,0x00,0xac,0x74,0xf6
DEFINE_GUIDSTRUCT("7b785572-8c82-11cf-bc0c-00aa00ac74f6", KSTIME_FORMAT_SAMPLE);
#define KSTIME_FORMAT_SAMPLE DEFINE_GUIDNAMED(KSTIME_FORMAT_SAMPLE)

#define STATIC_KSTIME_FORMAT_FIELD                  \
    0x7b785573L,0x8c82,0x11cf,0xbc,0x0c,0x00,0xaa,0x00,0xac,0x74,0xf6
DEFINE_GUIDSTRUCT("7b785573-8c82-11cf-bc0c-00aa00ac74f6", KSTIME_FORMAT_FIELD);
#define KSTIME_FORMAT_FIELD DEFINE_GUIDNAMED(KSTIME_FORMAT_FIELD)

#define STATIC_KSTIME_FORMAT_MEDIA_TIME                 \
    0x7b785574L,0x8c82,0x11cf,0xbc,0x0c,0x00,0xaa,0x00,0xac,0x74,0xf6
DEFINE_GUIDSTRUCT("7b785574-8c82-11cf-bc0c-00aa00ac74f6", KSTIME_FORMAT_MEDIA_TIME);
#define KSTIME_FORMAT_MEDIA_TIME DEFINE_GUIDNAMED(KSTIME_FORMAT_MEDIA_TIME)

typedef KSIDENTIFIER KSPIN_INTERFACE, *PKSPIN_INTERFACE;

#define STATIC_KSINTERFACESETID_Standard                \
    0x1A8766A0L,0x62CE,0x11CF,0xA5,0xD6,0x28,0xDB,0x04,0xC1,0x00,0x00
DEFINE_GUIDSTRUCT("1A8766A0-62CE-11CF-A5D6-28DB04C10000", KSINTERFACESETID_Standard);
#define KSINTERFACESETID_Standard DEFINE_GUIDNAMED(KSINTERFACESETID_Standard)

typedef enum {
    KSINTERFACE_STANDARD_STREAMING,
    KSINTERFACE_STANDARD_LOOPED_STREAMING,
    KSINTERFACE_STANDARD_CONTROL
} KSINTERFACE_STANDARD;

#define STATIC_KSINTERFACESETID_FileIo                  \
    0x8C6F932CL,0xE771,0x11D0,0xB8,0xFF,0x00,0xA0,0xC9,0x22,0x31,0x96
DEFINE_GUIDSTRUCT("8C6F932C-E771-11D0-B8FF-00A0C9223196", KSINTERFACESETID_FileIo);
#define KSINTERFACESETID_FileIo DEFINE_GUIDNAMED(KSINTERFACESETID_FileIo)

typedef enum {
    KSINTERFACE_FILEIO_STREAMING
} KSINTERFACE_FILEIO;

#define KSMEDIUM_TYPE_ANYINSTANCE       0

#define STATIC_KSMEDIUMSETID_Standard                   \
    0x4747B320L,0x62CE,0x11CF,0xA5,0xD6,0x28,0xDB,0x04,0xC1,0x00,0x00
DEFINE_GUIDSTRUCT("4747B320-62CE-11CF-A5D6-28DB04C10000", KSMEDIUMSETID_Standard);
#define KSMEDIUMSETID_Standard DEFINE_GUIDNAMED(KSMEDIUMSETID_Standard)

#define KSMEDIUM_STANDARD_DEVIO KSMEDIUM_TYPE_ANYINSTANCE

#define STATIC_KSPROPSETID_Pin                      \
    0x8C134960L,0x51AD,0x11CF,0x87,0x8A,0x94,0xF8,0x01,0xC1,0x00,0x00
DEFINE_GUIDSTRUCT("8C134960-51AD-11CF-878A-94F801C10000", KSPROPSETID_Pin);
#define KSPROPSETID_Pin DEFINE_GUIDNAMED(KSPROPSETID_Pin)

typedef enum {
    KSPROPERTY_PIN_CINSTANCES,
    KSPROPERTY_PIN_CTYPES,
    KSPROPERTY_PIN_DATAFLOW,
    KSPROPERTY_PIN_DATARANGES,
    KSPROPERTY_PIN_DATAINTERSECTION,
    KSPROPERTY_PIN_INTERFACES,
    KSPROPERTY_PIN_MEDIUMS,
    KSPROPERTY_PIN_COMMUNICATION,
    KSPROPERTY_PIN_GLOBALCINSTANCES,
    KSPROPERTY_PIN_NECESSARYINSTANCES,
    KSPROPERTY_PIN_PHYSICALCONNECTION,
    KSPROPERTY_PIN_CATEGORY,
    KSPROPERTY_PIN_NAME,
    KSPROPERTY_PIN_CONSTRAINEDDATARANGES,
    KSPROPERTY_PIN_PROPOSEDATAFORMAT
} KSPROPERTY_PIN;

typedef struct {
    KSPROPERTY Property;
    ULONG PinId;
    ULONG Reserved;
} KSP_PIN, *PKSP_PIN;

#define KSINSTANCE_INDETERMINATE    ((ULONG)-1)

typedef struct {
    ULONG PossibleCount;
    ULONG CurrentCount;
} KSPIN_CINSTANCES, *PKSPIN_CINSTANCES;

typedef enum {
    KSPIN_DATAFLOW_IN = 1,
    KSPIN_DATAFLOW_OUT
} KSPIN_DATAFLOW, *PKSPIN_DATAFLOW;

#define KSDATAFORMAT_BIT_TEMPORAL_COMPRESSION   0
#define KSDATAFORMAT_TEMPORAL_COMPRESSION   (1 << KSDATAFORMAT_BIT_TEMPORAL_COMPRESSION)
#define KSDATAFORMAT_BIT_ATTRIBUTES     1
#define KSDATAFORMAT_ATTRIBUTES         (1 << KSDATAFORMAT_BIT_ATTRIBUTES)

#define KSDATARANGE_BIT_ATTRIBUTES      1
#define KSDATARANGE_ATTRIBUTES          (1 << KSDATARANGE_BIT_ATTRIBUTES)
#define KSDATARANGE_BIT_REQUIRED_ATTRIBUTES 2
#define KSDATARANGE_REQUIRED_ATTRIBUTES     (1 << KSDATARANGE_BIT_REQUIRED_ATTRIBUTES)

typedef union {
    __MINGW_EXTENSION struct {
        ULONG FormatSize;
        ULONG Flags;
        ULONG SampleSize;
        ULONG Reserved;
        GUID MajorFormat;
        GUID SubFormat;
        GUID Specifier;
    };
    LONGLONG Alignment;
} KSDATAFORMAT, *PKSDATAFORMAT, KSDATARANGE, *PKSDATARANGE;

#define KSATTRIBUTE_REQUIRED        0x00000001

typedef struct {
    ULONG Size;
    ULONG Flags;
    GUID Attribute;
} KSATTRIBUTE, *PKSATTRIBUTE;

#if defined(_NTDDK_)
typedef struct {
    ULONG Count;
    PKSATTRIBUTE *Attributes;
} KSATTRIBUTE_LIST, *PKSATTRIBUTE_LIST;
#endif /* #if defined(_NTDDK_) */

typedef enum {
    KSPIN_COMMUNICATION_NONE,
    KSPIN_COMMUNICATION_SINK,
    KSPIN_COMMUNICATION_SOURCE,
    KSPIN_COMMUNICATION_BOTH,
    KSPIN_COMMUNICATION_BRIDGE
} KSPIN_COMMUNICATION, *PKSPIN_COMMUNICATION;

typedef KSIDENTIFIER KSPIN_MEDIUM, *PKSPIN_MEDIUM;

typedef struct {
    KSPIN_INTERFACE Interface;
    KSPIN_MEDIUM Medium;
    ULONG PinId;
    HANDLE PinToHandle;
    KSPRIORITY Priority;
} KSPIN_CONNECT, *PKSPIN_CONNECT;

typedef struct {
    ULONG Size;
    ULONG Pin;
    WCHAR SymbolicLinkName[1];
} KSPIN_PHYSICALCONNECTION, *PKSPIN_PHYSICALCONNECTION;

#if defined(_NTDDK_)
typedef NTSTATUS(*PFNKSINTERSECTHANDLER)(PIRP Irp, PKSP_PIN Pin,
                                         PKSDATARANGE DataRange,
                                         PVOID Data);
typedef NTSTATUS(*PFNKSINTERSECTHANDLEREX)(PVOID Context, PIRP Irp,
                                           PKSP_PIN Pin,
                                           PKSDATARANGE DataRange,
                                           PKSDATARANGE MatchingDataRange,
                                           ULONG DataBufferSize,
                                           PVOID Data,
                                           PULONG DataSize);
#endif /* #if defined(_NTDDK_) */

#define DEFINE_KSPIN_INTERFACE_TABLE(tablename)             \
    const KSPIN_INTERFACE tablename[] =

#define DEFINE_KSPIN_INTERFACE_ITEM(guid,_interFace)            \
    {                               \
        STATICGUIDOF(guid),                 \
        (_interFace),                       \
        0                           \
    }

#define DEFINE_KSPIN_MEDIUM_TABLE(tablename)                \
    const KSPIN_MEDIUM tablename[] =

#define DEFINE_KSPIN_MEDIUM_ITEM(guid,medium)               \
        DEFINE_KSPIN_INTERFACE_ITEM(guid,medium)

#define DEFINE_KSPROPERTY_ITEM_PIN_CINSTANCES(Handler)          \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_PIN_CINSTANCES,      \
                (Handler),              \
                sizeof(KSP_PIN),            \
                sizeof(KSPIN_CINSTANCES),       \
                NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_PIN_CTYPES(Handler)          \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_PIN_CTYPES,          \
                (Handler),              \
                sizeof(KSPROPERTY),         \
                sizeof(ULONG),              \
                NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_PIN_DATAFLOW(Handler)            \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_PIN_DATAFLOW,        \
                (Handler),              \
                sizeof(KSP_PIN),            \
                sizeof(KSPIN_DATAFLOW),         \
                NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_PIN_DATARANGES(Handler)          \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_PIN_DATARANGES,      \
                (Handler),              \
                sizeof(KSP_PIN),            \
                0,                  \
                NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_PIN_DATAINTERSECTION(Handler)        \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_PIN_DATAINTERSECTION,    \
                (Handler),              \
                sizeof(KSP_PIN) + sizeof(KSMULTIPLE_ITEM),\
                0,                  \
                NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_PIN_INTERFACES(Handler)          \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_PIN_INTERFACES,      \
                (Handler),              \
                sizeof(KSP_PIN),            \
                0,                  \
                NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_PIN_MEDIUMS(Handler)         \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_PIN_MEDIUMS,         \
                (Handler),              \
                sizeof(KSP_PIN),            \
                0,                  \
                NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_PIN_COMMUNICATION(Handler)       \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_PIN_COMMUNICATION,       \
                (Handler),              \
                sizeof(KSP_PIN),            \
                sizeof(KSPIN_COMMUNICATION),        \
                NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_PIN_GLOBALCINSTANCES(Handler)        \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_PIN_GLOBALCINSTANCES,    \
                (Handler),              \
                sizeof(KSP_PIN),            \
                sizeof(KSPIN_CINSTANCES),       \
                NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_PIN_NECESSARYINSTANCES(Handler)      \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_PIN_NECESSARYINSTANCES,  \
                (Handler),              \
                sizeof(KSP_PIN),            \
                sizeof(ULONG),              \
                NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_PIN_PHYSICALCONNECTION(Handler)      \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_PIN_PHYSICALCONNECTION,  \
                (Handler),              \
                sizeof(KSP_PIN),            \
                0,                  \
                NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_PIN_CATEGORY(Handler)            \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_PIN_CATEGORY,        \
                (Handler),              \
                sizeof(KSP_PIN),            \
                sizeof(GUID),               \
                NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_PIN_NAME(Handler)            \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_PIN_NAME,            \
                (Handler),              \
                sizeof(KSP_PIN),            \
                0,                  \
                NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_PIN_CONSTRAINEDDATARANGES(Handler)   \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_PIN_CONSTRAINEDDATARANGES,   \
                (Handler),              \
                sizeof(KSP_PIN),            \
                0,                  \
                NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_PIN_PROPOSEDATAFORMAT(Handler)       \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_PIN_PROPOSEDATAFORMAT,   \
                NULL,                   \
                sizeof(KSP_PIN),            \
                sizeof(KSDATAFORMAT),           \
                (Handler), NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_PINSET(PinSet,PropGeneral,PropInstances,PropIntersection) \
DEFINE_KSPROPERTY_TABLE(PinSet) {                   \
    DEFINE_KSPROPERTY_ITEM_PIN_CINSTANCES(PropInstances),       \
    DEFINE_KSPROPERTY_ITEM_PIN_CTYPES(PropGeneral),         \
    DEFINE_KSPROPERTY_ITEM_PIN_DATAFLOW(PropGeneral),       \
    DEFINE_KSPROPERTY_ITEM_PIN_DATARANGES(PropGeneral),     \
    DEFINE_KSPROPERTY_ITEM_PIN_DATAINTERSECTION(PropIntersection),  \
    DEFINE_KSPROPERTY_ITEM_PIN_INTERFACES(PropGeneral),     \
    DEFINE_KSPROPERTY_ITEM_PIN_MEDIUMS(PropGeneral),        \
    DEFINE_KSPROPERTY_ITEM_PIN_COMMUNICATION(PropGeneral),      \
    DEFINE_KSPROPERTY_ITEM_PIN_CATEGORY(PropGeneral),       \
    DEFINE_KSPROPERTY_ITEM_PIN_NAME(PropGeneral)            \
}

#define DEFINE_KSPROPERTY_PINSETCONSTRAINED(PinSet,PropGeneral,PropInstances,PropIntersection) \
DEFINE_KSPROPERTY_TABLE(PinSet) {                   \
    DEFINE_KSPROPERTY_ITEM_PIN_CINSTANCES(PropInstances),       \
    DEFINE_KSPROPERTY_ITEM_PIN_CTYPES(PropGeneral),         \
    DEFINE_KSPROPERTY_ITEM_PIN_DATAFLOW(PropGeneral),       \
    DEFINE_KSPROPERTY_ITEM_PIN_DATARANGES(PropGeneral),     \
    DEFINE_KSPROPERTY_ITEM_PIN_DATAINTERSECTION(PropIntersection),  \
    DEFINE_KSPROPERTY_ITEM_PIN_INTERFACES(PropGeneral),     \
    DEFINE_KSPROPERTY_ITEM_PIN_MEDIUMS(PropGeneral),        \
    DEFINE_KSPROPERTY_ITEM_PIN_COMMUNICATION(PropGeneral),      \
    DEFINE_KSPROPERTY_ITEM_PIN_CATEGORY(PropGeneral),       \
    DEFINE_KSPROPERTY_ITEM_PIN_NAME(PropGeneral),           \
    DEFINE_KSPROPERTY_ITEM_PIN_CONSTRAINEDDATARANGES(PropGeneral)   \
}

#define STATIC_KSNAME_Filter                        \
    0x9b365890L,0x165f,0x11d0,0xa1,0x95,0x00,0x20,0xaf,0xd1,0x56,0xe4
DEFINE_GUIDSTRUCT("9b365890-165f-11d0-a195-0020afd156e4", KSNAME_Filter);
#define KSNAME_Filter DEFINE_GUIDNAMED(KSNAME_Filter)

#define KSSTRING_Filter     L"{9B365890-165F-11D0-A195-0020AFD156E4}"

#define STATIC_KSNAME_Pin                       \
    0x146F1A80L,0x4791,0x11D0,0xA5,0xD6,0x28,0xDB,0x04,0xC1,0x00,0x00
DEFINE_GUIDSTRUCT("146F1A80-4791-11D0-A5D6-28DB04C10000", KSNAME_Pin);
#define KSNAME_Pin DEFINE_GUIDNAMED(KSNAME_Pin)

#define KSSTRING_Pin        L"{146F1A80-4791-11D0-A5D6-28DB04C10000}"

#define STATIC_KSNAME_Clock                     \
    0x53172480L,0x4791,0x11D0,0xA5,0xD6,0x28,0xDB,0x04,0xC1,0x00,0x00
DEFINE_GUIDSTRUCT("53172480-4791-11D0-A5D6-28DB04C10000", KSNAME_Clock);
#define KSNAME_Clock DEFINE_GUIDNAMED(KSNAME_Clock)

#define KSSTRING_Clock      L"{53172480-4791-11D0-A5D6-28DB04C10000}"

#define STATIC_KSNAME_Allocator                     \
    0x642F5D00L,0x4791,0x11D0,0xA5,0xD6,0x28,0xDB,0x04,0xC1,0x00,0x00
DEFINE_GUIDSTRUCT("642F5D00-4791-11D0-A5D6-28DB04C10000", KSNAME_Allocator);
#define KSNAME_Allocator DEFINE_GUIDNAMED(KSNAME_Allocator)

#define KSSTRING_Allocator  L"{642F5D00-4791-11D0-A5D6-28DB04C10000}"

#define KSSTRING_AllocatorEx    L"{091BB63B-603F-11D1-B067-00A0C9062802}"

#define STATIC_KSNAME_TopologyNode                  \
    0x0621061AL,0xEE75,0x11D0,0xB9,0x15,0x00,0xA0,0xC9,0x22,0x31,0x96
DEFINE_GUIDSTRUCT("0621061A-EE75-11D0-B915-00A0C9223196", KSNAME_TopologyNode);
#define KSNAME_TopologyNode DEFINE_GUIDNAMED(KSNAME_TopologyNode)

#define KSSTRING_TopologyNode   L"{0621061A-EE75-11D0-B915-00A0C9223196}"

#if defined(_NTDDK_)
typedef struct {
    ULONG InterfacesCount;
    const KSPIN_INTERFACE *Interfaces;
    ULONG MediumsCount;
    const KSPIN_MEDIUM *Mediums;
    ULONG DataRangesCount;
    const PKSDATARANGE *DataRanges;
    KSPIN_DATAFLOW DataFlow;
    KSPIN_COMMUNICATION Communication;
    const GUID *Category;
    const GUID *Name;
    __MINGW_EXTENSION union {
        LONGLONG Reserved;
        __MINGW_EXTENSION struct {
            ULONG ConstrainedDataRangesCount;
            PKSDATARANGE *ConstrainedDataRanges;
        };
    };
} KSPIN_DESCRIPTOR, *PKSPIN_DESCRIPTOR;
typedef const KSPIN_DESCRIPTOR *PCKSPIN_DESCRIPTOR;

#define DEFINE_KSPIN_DESCRIPTOR_TABLE(tablename)            \
    const KSPIN_DESCRIPTOR tablename[] =

#define DEFINE_KSPIN_DESCRIPTOR_ITEM(InterfacesCount,Interfaces,MediumsCount, Mediums,DataRangesCount,DataRanges,DataFlow,Communication)\
{                                   \
        InterfacesCount, Interfaces, MediumsCount, Mediums, \
        DataRangesCount, DataRanges, DataFlow, Communication,   \
        NULL, NULL, 0                       \
}

#define DEFINE_KSPIN_DESCRIPTOR_ITEMEX(InterfacesCount,Interfaces,MediumsCount,Mediums,DataRangesCount,DataRanges,DataFlow,Communication,Category,Name)\
{                                   \
        InterfacesCount, Interfaces, MediumsCount, Mediums, \
        DataRangesCount, DataRanges, DataFlow, Communication,   \
        Category, Name, 0                   \
}
#endif /* #if defined(_NTDDK_) */

#define STATIC_KSDATAFORMAT_TYPE_WILDCARD   STATIC_GUID_NULL
#define KSDATAFORMAT_TYPE_WILDCARD      GUID_NULL

#define STATIC_KSDATAFORMAT_SUBTYPE_WILDCARD    STATIC_GUID_NULL
#define KSDATAFORMAT_SUBTYPE_WILDCARD       GUID_NULL

#define STATIC_KSDATAFORMAT_TYPE_STREAM                 \
    0xE436EB83L,0x524F,0x11CE,0x9F,0x53,0x00,0x20,0xAF,0x0B,0xA7,0x70
DEFINE_GUIDSTRUCT("E436EB83-524F-11CE-9F53-0020AF0BA770", KSDATAFORMAT_TYPE_STREAM);
#define KSDATAFORMAT_TYPE_STREAM DEFINE_GUIDNAMED(KSDATAFORMAT_TYPE_STREAM)

#define STATIC_KSDATAFORMAT_SUBTYPE_NONE                \
    0xE436EB8EL,0x524F,0x11CE,0x9F,0x53,0x00,0x20,0xAF,0x0B,0xA7,0x70
DEFINE_GUIDSTRUCT("E436EB8E-524F-11CE-9F53-0020AF0BA770", KSDATAFORMAT_SUBTYPE_NONE);
#define KSDATAFORMAT_SUBTYPE_NONE DEFINE_GUIDNAMED(KSDATAFORMAT_SUBTYPE_NONE)

#define STATIC_KSDATAFORMAT_SPECIFIER_WILDCARD  STATIC_GUID_NULL
#define KSDATAFORMAT_SPECIFIER_WILDCARD     GUID_NULL

#define STATIC_KSDATAFORMAT_SPECIFIER_FILENAME              \
    0xAA797B40L,0xE974,0x11CF,0xA5,0xD6,0x28,0xDB,0x04,0xC1,0x00,0x00
DEFINE_GUIDSTRUCT("AA797B40-E974-11CF-A5D6-28DB04C10000", KSDATAFORMAT_SPECIFIER_FILENAME);
#define KSDATAFORMAT_SPECIFIER_FILENAME DEFINE_GUIDNAMED(KSDATAFORMAT_SPECIFIER_FILENAME)

#define STATIC_KSDATAFORMAT_SPECIFIER_FILEHANDLE            \
    0x65E8773CL,0x8F56,0x11D0,0xA3,0xB9,0x00,0xA0,0xC9,0x22,0x31,0x96
DEFINE_GUIDSTRUCT("65E8773C-8F56-11D0-A3B9-00A0C9223196", KSDATAFORMAT_SPECIFIER_FILEHANDLE);
#define KSDATAFORMAT_SPECIFIER_FILEHANDLE DEFINE_GUIDNAMED(KSDATAFORMAT_SPECIFIER_FILEHANDLE)

#define STATIC_KSDATAFORMAT_SPECIFIER_NONE              \
    0x0F6417D6L,0xC318,0x11D0,0xA4,0x3F,0x00,0xA0,0xC9,0x22,0x31,0x96
DEFINE_GUIDSTRUCT("0F6417D6-C318-11D0-A43F-00A0C9223196", KSDATAFORMAT_SPECIFIER_NONE);
#define KSDATAFORMAT_SPECIFIER_NONE DEFINE_GUIDNAMED(KSDATAFORMAT_SPECIFIER_NONE)

#define STATIC_KSPROPSETID_Quality                  \
    0xD16AD380L,0xAC1A,0x11CF,0xA5,0xD6,0x28,0xDB,0x04,0xC1,0x00,0x00
DEFINE_GUIDSTRUCT("D16AD380-AC1A-11CF-A5D6-28DB04C10000", KSPROPSETID_Quality);
#define KSPROPSETID_Quality DEFINE_GUIDNAMED(KSPROPSETID_Quality)

typedef enum {
    KSPROPERTY_QUALITY_REPORT,
    KSPROPERTY_QUALITY_ERROR
} KSPROPERTY_QUALITY;

#define DEFINE_KSPROPERTY_ITEM_QUALITY_REPORT(GetHandler,SetHandler)    \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_QUALITY_REPORT,      \
                (GetHandler),               \
                sizeof(KSPROPERTY),         \
                sizeof(KSQUALITY),          \
                (SetHandler),               \
                NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_QUALITY_ERROR(GetHandler,SetHandler) \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_QUALITY_ERROR,       \
                (GetHandler),               \
                sizeof(KSPROPERTY),         \
                sizeof(KSERROR),            \
                (SetHandler),               \
                NULL, 0, NULL, NULL, 0)

#define STATIC_KSPROPSETID_Connection                   \
    0x1D58C920L,0xAC9B,0x11CF,0xA5,0xD6,0x28,0xDB,0x04,0xC1,0x00,0x00
DEFINE_GUIDSTRUCT("1D58C920-AC9B-11CF-A5D6-28DB04C10000", KSPROPSETID_Connection);
#define KSPROPSETID_Connection DEFINE_GUIDNAMED(KSPROPSETID_Connection)

typedef enum {
    KSPROPERTY_CONNECTION_STATE,
    KSPROPERTY_CONNECTION_PRIORITY,
    KSPROPERTY_CONNECTION_DATAFORMAT,
    KSPROPERTY_CONNECTION_ALLOCATORFRAMING,
    KSPROPERTY_CONNECTION_PROPOSEDATAFORMAT,
    KSPROPERTY_CONNECTION_ACQUIREORDERING,
    KSPROPERTY_CONNECTION_ALLOCATORFRAMING_EX,
    KSPROPERTY_CONNECTION_STARTAT
} KSPROPERTY_CONNECTION;

#define DEFINE_KSPROPERTY_ITEM_CONNECTION_STATE(GetHandler,SetHandler)  \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_CONNECTION_STATE,        \
                (GetHandler),               \
                sizeof(KSPROPERTY),         \
                sizeof(KSSTATE),            \
                (SetHandler),               \
                NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_CONNECTION_PRIORITY(GetHandler,SetHandler) \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_CONNECTION_PRIORITY,     \
                (GetHandler),               \
                sizeof(KSPROPERTY),         \
                sizeof(KSPRIORITY),         \
                (SetHandler),               \
                NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_CONNECTION_DATAFORMAT(GetHandler,SetHandler)\
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_CONNECTION_DATAFORMAT,   \
                (GetHandler),               \
                sizeof(KSPROPERTY),         \
                0,                  \
                (SetHandler),               \
                NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_CONNECTION_ALLOCATORFRAMING(Handler) \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_CONNECTION_ALLOCATORFRAMING, \
                (Handler),              \
                sizeof(KSPROPERTY),         \
                sizeof(KSALLOCATOR_FRAMING),        \
                NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_CONNECTION_ALLOCATORFRAMING_EX(Handler)  \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_CONNECTION_ALLOCATORFRAMING_EX,\
                (Handler),              \
                sizeof(KSPROPERTY),         \
                0,                  \
                NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_CONNECTION_PROPOSEDATAFORMAT(Handler)    \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_CONNECTION_PROPOSEDATAFORMAT,\
                NULL,                   \
                sizeof(KSPROPERTY),         \
                sizeof(KSDATAFORMAT),           \
                (Handler),              \
                NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_CONNECTION_ACQUIREORDERING(Handler)  \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_CONNECTION_ACQUIREORDERING,  \
                (Handler),              \
                sizeof(KSPROPERTY),         \
                sizeof(int),                \
                NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_CONNECTION_STARTAT(Handler)      \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_CONNECTION_STARTAT,      \
                NULL,                   \
                sizeof(KSPROPERTY),         \
                sizeof(KSRELATIVEEVENT),        \
                (Handler),              \
                NULL, 0, NULL, NULL, 0)

#define KSALLOCATOR_REQUIREMENTF_INPLACE_MODIFIER   0x00000001
#define KSALLOCATOR_REQUIREMENTF_SYSTEM_MEMORY      0x00000002
#define KSALLOCATOR_REQUIREMENTF_FRAME_INTEGRITY    0x00000004
#define KSALLOCATOR_REQUIREMENTF_MUST_ALLOCATE      0x00000008
#define KSALLOCATOR_REQUIREMENTF_PREFERENCES_ONLY   0x80000000

#define KSALLOCATOR_OPTIONF_COMPATIBLE          0x00000001
#define KSALLOCATOR_OPTIONF_SYSTEM_MEMORY       0x00000002
#define KSALLOCATOR_OPTIONF_VALID           0x00000003

#define KSALLOCATOR_FLAG_PARTIAL_READ_SUPPORT       0x00000010
#define KSALLOCATOR_FLAG_DEVICE_SPECIFIC        0x00000020
#define KSALLOCATOR_FLAG_CAN_ALLOCATE           0x00000040
#define KSALLOCATOR_FLAG_INSIST_ON_FRAMESIZE_RATIO  0x00000080
#define KSALLOCATOR_FLAG_NO_FRAME_INTEGRITY     0x00000100
#define KSALLOCATOR_FLAG_MULTIPLE_OUTPUT        0x00000200
#define KSALLOCATOR_FLAG_CYCLE              0x00000400
#define KSALLOCATOR_FLAG_ALLOCATOR_EXISTS       0x00000800
#define KSALLOCATOR_FLAG_INDEPENDENT_RANGES     0x00001000
#define KSALLOCATOR_FLAG_ATTENTION_STEPPING     0x00002000

typedef struct {
    __MINGW_EXTENSION union {
        ULONG OptionsFlags;
        ULONG RequirementsFlags;
    };
#if defined(_NTDDK_)
    POOL_TYPE PoolType;
#else /* #if defined(_NTDDK_) */
    ULONG PoolType;
#endif /* #if defined(_NTDDK_) */
    ULONG Frames;
    ULONG FrameSize;
    ULONG FileAlignment;
    ULONG Reserved;
} KSALLOCATOR_FRAMING, *PKSALLOCATOR_FRAMING;

#if defined(_NTDDK_)
typedef PVOID(*PFNKSDEFAULTALLOCATE)(PVOID Context);
typedef VOID (*PFNKSDEFAULTFREE)(PVOID Context, PVOID Buffer);
typedef NTSTATUS(*PFNKSINITIALIZEALLOCATOR)(PVOID InitialContext,
                                            PKSALLOCATOR_FRAMING AllocatorFraming,
                                            PVOID *Context);
typedef VOID (*PFNKSDELETEALLOCATOR)(PVOID Context);
#endif /* #if defined(_NTDDK_) */

typedef struct {
    ULONG MinFrameSize;
    ULONG MaxFrameSize;
    ULONG Stepping;
} KS_FRAMING_RANGE, *PKS_FRAMING_RANGE;

typedef struct {
    KS_FRAMING_RANGE Range;
    ULONG InPlaceWeight;
    ULONG NotInPlaceWeight;
} KS_FRAMING_RANGE_WEIGHTED, *PKS_FRAMING_RANGE_WEIGHTED;

typedef struct {
    ULONG RatioNumerator;
    ULONG RatioDenominator;
    ULONG RatioConstantMargin;
} KS_COMPRESSION, *PKS_COMPRESSION;

typedef struct {
    GUID MemoryType;
    GUID BusType;
    ULONG MemoryFlags;
    ULONG BusFlags;
    ULONG Flags;
    ULONG Frames;
    ULONG FileAlignment;
    ULONG MemoryTypeWeight;
    KS_FRAMING_RANGE PhysicalRange;
    KS_FRAMING_RANGE_WEIGHTED FramingRange;
} KS_FRAMING_ITEM, *PKS_FRAMING_ITEM;

typedef struct {
    ULONG CountItems;
    ULONG PinFlags;
    KS_COMPRESSION OutputCompression;
    ULONG PinWeight;
    KS_FRAMING_ITEM FramingItem[1];
} KSALLOCATOR_FRAMING_EX, *PKSALLOCATOR_FRAMING_EX;

#define KSMEMORY_TYPE_WILDCARD      GUID_NULL
#define STATIC_KSMEMORY_TYPE_WILDCARD   STATIC_GUID_NULL

#define KSMEMORY_TYPE_DONT_CARE     GUID_NULL
#define STATIC_KSMEMORY_TYPE_DONT_CARE  STATIC_GUID_NULL

#define KS_TYPE_DONT_CARE       GUID_NULL
#define STATIC_KS_TYPE_DONT_CARE    STATIC_GUID_NULL

#define STATIC_KSMEMORY_TYPE_SYSTEM                 \
    0x091bb638L,0x603f,0x11d1,0xb0,0x67,0x00,0xa0,0xc9,0x06,0x28,0x02
DEFINE_GUIDSTRUCT("091bb638-603f-11d1-b067-00a0c9062802", KSMEMORY_TYPE_SYSTEM);
#define KSMEMORY_TYPE_SYSTEM DEFINE_GUIDNAMED(KSMEMORY_TYPE_SYSTEM)

#define STATIC_KSMEMORY_TYPE_USER                   \
    0x8cb0fc28L,0x7893,0x11d1,0xb0,0x69,0x00,0xa0,0xc9,0x06,0x28,0x02
DEFINE_GUIDSTRUCT("8cb0fc28-7893-11d1-b069-00a0c9062802", KSMEMORY_TYPE_USER);
#define KSMEMORY_TYPE_USER DEFINE_GUIDNAMED(KSMEMORY_TYPE_USER)

#define STATIC_KSMEMORY_TYPE_KERNEL_PAGED               \
    0xd833f8f8L,0x7894,0x11d1,0xb0,0x69,0x00,0xa0,0xc9,0x06,0x28,0x02
DEFINE_GUIDSTRUCT("d833f8f8-7894-11d1-b069-00a0c9062802", KSMEMORY_TYPE_KERNEL_PAGED);
#define KSMEMORY_TYPE_KERNEL_PAGED DEFINE_GUIDNAMED(KSMEMORY_TYPE_KERNEL_PAGED)

#define STATIC_KSMEMORY_TYPE_KERNEL_NONPAGED                \
    0x4a6d5fc4L,0x7895,0x11d1,0xb0,0x69,0x00,0xa0,0xc9,0x06,0x28,0x02
DEFINE_GUIDSTRUCT("4a6d5fc4-7895-11d1-b069-00a0c9062802", KSMEMORY_TYPE_KERNEL_NONPAGED);
#define KSMEMORY_TYPE_KERNEL_NONPAGED DEFINE_GUIDNAMED(KSMEMORY_TYPE_KERNEL_NONPAGED)

#define STATIC_KSMEMORY_TYPE_DEVICE_UNKNOWN             \
    0x091bb639L,0x603f,0x11d1,0xb0,0x67,0x00,0xa0,0xc9,0x06,0x28,0x02
DEFINE_GUIDSTRUCT("091bb639-603f-11d1-b067-00a0c9062802", KSMEMORY_TYPE_DEVICE_UNKNOWN);
#define KSMEMORY_TYPE_DEVICE_UNKNOWN DEFINE_GUIDNAMED(KSMEMORY_TYPE_DEVICE_UNKNOWN)

#define DECLARE_SIMPLE_FRAMING_EX(FramingExName,MemoryType,Flags,Frames,Alignment,MinFrameSize,MaxFrameSize) \
const KSALLOCATOR_FRAMING_EX FramingExName =                \
{                                   \
    1,                              \
    0,                              \
    {                               \
        1,                          \
        1,                          \
        0                           \
    },                              \
    0,                              \
    {                               \
        {                           \
            MemoryType,                 \
            STATIC_KS_TYPE_DONT_CARE,           \
            0,                      \
            0,                      \
            Flags,                      \
            Frames,                     \
            Alignment,                  \
            0,                      \
            {                       \
                0,                  \
                (ULONG)-1,              \
                1                   \
            },                      \
            {                       \
                {                   \
                    MinFrameSize,           \
                    MaxFrameSize,           \
                    1               \
                },                  \
                0,                  \
                0                   \
            }                       \
        }                           \
    }                               \
}

#define SetDefaultKsCompression(KsCompressionPointer)           \
{                                   \
    KsCompressionPointer->RatioNumerator = 1;           \
    KsCompressionPointer->RatioDenominator = 1;         \
    KsCompressionPointer->RatioConstantMargin = 0;          \
}

#define SetDontCareKsFramingRange(KsFramingRangePointer)        \
{                                   \
    KsFramingRangePointer->MinFrameSize = 0;            \
    KsFramingRangePointer->MaxFrameSize = (ULONG) -1;       \
    KsFramingRangePointer->Stepping = 1;                \
}

#define SetKsFramingRange(KsFramingRangePointer,P_MinFrameSize,P_MaxFrameSize) \
{                                   \
    KsFramingRangePointer->MinFrameSize = P_MinFrameSize;       \
    KsFramingRangePointer->MaxFrameSize = P_MaxFrameSize;       \
    KsFramingRangePointer->Stepping = 1;                \
}

#define SetKsFramingRangeWeighted(KsFramingRangeWeightedPointer,P_MinFrameSize,P_MaxFrameSize) \
{                                   \
    KS_FRAMING_RANGE *KsFramingRange =              \
                &KsFramingRangeWeightedPointer->Range;  \
    SetKsFramingRange(KsFramingRange,P_MinFrameSize,P_MaxFrameSize);\
    KsFramingRangeWeightedPointer->InPlaceWeight = 0;       \
    KsFramingRangeWeightedPointer->NotInPlaceWeight = 0;        \
}

#define INITIALIZE_SIMPLE_FRAMING_EX(FramingExPointer,P_MemoryType,P_Flags,P_Frames,P_Alignment,P_MinFrameSize,P_MaxFrameSize) \
{                                   \
    KS_COMPRESSION *KsCompression =                 \
            &FramingExPointer->OutputCompression;       \
    KS_FRAMING_RANGE *KsFramingRange =              \
            &FramingExPointer->FramingItem[0].PhysicalRange;\
    KS_FRAMING_RANGE_WEIGHTED *KsFramingRangeWeighted =     \
            &FramingExPointer->FramingItem[0].FramingRange; \
    FramingExPointer->CountItems = 1;               \
    FramingExPointer->PinFlags = 0;                 \
    SetDefaultKsCompression(KsCompression);             \
    FramingExPointer->PinWeight = 0;                \
    FramingExPointer->FramingItem[0].MemoryType = P_MemoryType; \
    FramingExPointer->FramingItem[0].BusType = KS_TYPE_DONT_CARE;   \
    FramingExPointer->FramingItem[0].MemoryFlags = 0;       \
    FramingExPointer->FramingItem[0].BusFlags = 0;          \
    FramingExPointer->FramingItem[0].Flags = P_Flags;       \
    FramingExPointer->FramingItem[0].Frames = P_Frames;     \
    FramingExPointer->FramingItem[0].FileAlignment = P_Alignment;   \
    FramingExPointer->FramingItem[0].MemoryTypeWeight = 0;      \
    SetDontCareKsFramingRange(KsFramingRange);          \
    SetKsFramingRangeWeighted(KsFramingRangeWeighted,       \
                  P_MinFrameSize,P_MaxFrameSize);   \
}

#define STATIC_KSEVENTSETID_StreamAllocator             \
    0x75d95571L,0x073c,0x11d0,0xa1,0x61,0x00,0x20,0xaf,0xd1,0x56,0xe4
DEFINE_GUIDSTRUCT("75d95571-073c-11d0-a161-0020afd156e4", KSEVENTSETID_StreamAllocator);
#define KSEVENTSETID_StreamAllocator DEFINE_GUIDNAMED(KSEVENTSETID_StreamAllocator)

typedef enum {
    KSEVENT_STREAMALLOCATOR_INTERNAL_FREEFRAME,
    KSEVENT_STREAMALLOCATOR_FREEFRAME
} KSEVENT_STREAMALLOCATOR;

#define STATIC_KSMETHODSETID_StreamAllocator                \
    0xcf6e4341L,0xec87,0x11cf,0xa1,0x30,0x00,0x20,0xaf,0xd1,0x56,0xe4
DEFINE_GUIDSTRUCT("cf6e4341-ec87-11cf-a130-0020afd156e4", KSMETHODSETID_StreamAllocator);
#define KSMETHODSETID_StreamAllocator DEFINE_GUIDNAMED(KSMETHODSETID_StreamAllocator)

typedef enum {
    KSMETHOD_STREAMALLOCATOR_ALLOC,
    KSMETHOD_STREAMALLOCATOR_FREE
} KSMETHOD_STREAMALLOCATOR;

#define DEFINE_KSMETHOD_ITEM_STREAMALLOCATOR_ALLOC(Handler)     \
    DEFINE_KSMETHOD_ITEM(                       \
                KSMETHOD_STREAMALLOCATOR_ALLOC,     \
                KSMETHOD_TYPE_WRITE,            \
                (Handler),              \
                sizeof(KSMETHOD),           \
                sizeof(PVOID),              \
                NULL)

#define DEFINE_KSMETHOD_ITEM_STREAMALLOCATOR_FREE(Handler)      \
    DEFINE_KSMETHOD_ITEM(                       \
                KSMETHOD_STREAMALLOCATOR_FREE,      \
                KSMETHOD_TYPE_READ,         \
                (Handler),              \
                sizeof(KSMETHOD),           \
                sizeof(PVOID),              \
                NULL)

#define DEFINE_KSMETHOD_ALLOCATORSET(AllocatorSet,MethodAlloc,MethodFree)\
DEFINE_KSMETHOD_TABLE(AllocatorSet) {                   \
    DEFINE_KSMETHOD_ITEM_STREAMALLOCATOR_ALLOC(MethodAlloc),    \
    DEFINE_KSMETHOD_ITEM_STREAMALLOCATOR_FREE(MethodFree)       \
}

#define STATIC_KSPROPSETID_StreamAllocator              \
    0xcf6e4342L,0xec87,0x11cf,0xa1,0x30,0x00,0x20,0xaf,0xd1,0x56,0xe4
DEFINE_GUIDSTRUCT("cf6e4342-ec87-11cf-a130-0020afd156e4", KSPROPSETID_StreamAllocator);
#define KSPROPSETID_StreamAllocator DEFINE_GUIDNAMED(KSPROPSETID_StreamAllocator)

#if defined(_NTDDK_)
typedef enum {
    KSPROPERTY_STREAMALLOCATOR_FUNCTIONTABLE,
    KSPROPERTY_STREAMALLOCATOR_STATUS
} KSPROPERTY_STREAMALLOCATOR;

#define DEFINE_KSPROPERTY_ITEM_STREAMALLOCATOR_FUNCTIONTABLE(Handler)   \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_STREAMALLOCATOR_FUNCTIONTABLE,\
                (Handler),              \
                sizeof(KSPROPERTY),         \
                sizeof(KSSTREAMALLOCATOR_FUNCTIONTABLE),\
                NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_STREAMALLOCATOR_STATUS(Handler)      \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_STREAMALLOCATOR_STATUS,  \
                (Handler),              \
                sizeof(KSPROPERTY),         \
                sizeof(KSSTREAMALLOCATOR_STATUS),   \
                NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ALLOCATORSET(AllocatorSet,PropFunctionTable,PropStatus)\
DEFINE_KSPROPERTY_TABLE(AllocatorSet) {                 \
    DEFINE_KSPROPERTY_ITEM_STREAMALLOCATOR_STATUS(PropStatus),  \
    DEFINE_KSPROPERTY_ITEM_STREAMALLOCATOR_FUNCTIONTABLE(PropFunctionTable)\
}

typedef NTSTATUS(*PFNALLOCATOR_ALLOCATEFRAME)(PFILE_OBJECT FileObject,
                                              PVOID *Frame);
typedef VOID (*PFNALLOCATOR_FREEFRAME)(PFILE_OBJECT FileObject, PVOID Frame);

typedef struct {
    PFNALLOCATOR_ALLOCATEFRAME AllocateFrame;
    PFNALLOCATOR_FREEFRAME FreeFrame;
} KSSTREAMALLOCATOR_FUNCTIONTABLE, *PKSSTREAMALLOCATOR_FUNCTIONTABLE;
#endif /* #if defined(_NTDDK_) */

typedef struct {
    KSALLOCATOR_FRAMING Framing;
    ULONG AllocatedFrames;
    ULONG Reserved;
} KSSTREAMALLOCATOR_STATUS, *PKSSTREAMALLOCATOR_STATUS;

typedef struct {
    KSALLOCATOR_FRAMING_EX Framing;
    ULONG AllocatedFrames;
    ULONG Reserved;
} KSSTREAMALLOCATOR_STATUS_EX, *PKSSTREAMALLOCATOR_STATUS_EX;

#define KSSTREAM_HEADER_OPTIONSF_SPLICEPOINT        0x00000001
#define KSSTREAM_HEADER_OPTIONSF_PREROLL        0x00000002
#define KSSTREAM_HEADER_OPTIONSF_DATADISCONTINUITY  0x00000004
#define KSSTREAM_HEADER_OPTIONSF_TYPECHANGED        0x00000008
#define KSSTREAM_HEADER_OPTIONSF_TIMEVALID      0x00000010
#define KSSTREAM_HEADER_OPTIONSF_TIMEDISCONTINUITY  0x00000040
#define KSSTREAM_HEADER_OPTIONSF_FLUSHONPAUSE       0x00000080
#define KSSTREAM_HEADER_OPTIONSF_DURATIONVALID      0x00000100
#define KSSTREAM_HEADER_OPTIONSF_ENDOFSTREAM        0x00000200
#define KSSTREAM_HEADER_OPTIONSF_LOOPEDDATA     0x80000000

typedef struct {
    LONGLONG Time;
    ULONG Numerator;
    ULONG Denominator;
} KSTIME, *PKSTIME;

typedef struct {
    ULONG Size;
    ULONG TypeSpecificFlags;
    KSTIME PresentationTime;
    LONGLONG Duration;
    ULONG FrameExtent;
    ULONG DataUsed;
    PVOID Data;
    ULONG OptionsFlags;
#ifdef _WIN64
    ULONG Reserved;
#endif /* #ifdef _WIN64 */
} KSSTREAM_HEADER, *PKSSTREAM_HEADER;

#define STATIC_KSPROPSETID_StreamInterface              \
    0x1fdd8ee1L,0x9cd3,0x11d0,0x82,0xaa,0x00,0x00,0xf8,0x22,0xfe,0x8a
DEFINE_GUIDSTRUCT("1fdd8ee1-9cd3-11d0-82aa-0000f822fe8a", KSPROPSETID_StreamInterface);
#define KSPROPSETID_StreamInterface DEFINE_GUIDNAMED(KSPROPSETID_StreamInterface)

typedef enum {
    KSPROPERTY_STREAMINTERFACE_HEADERSIZE
} KSPROPERTY_STREAMINTERFACE;

#define DEFINE_KSPROPERTY_ITEM_STREAMINTERFACE_HEADERSIZE(GetHandler)   \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_STREAMINTERFACE_HEADERSIZE,  \
                (GetHandler),               \
                sizeof(KSPROPERTY),         \
                sizeof(ULONG),              \
                NULL,NULL,0,NULL,NULL,0)

#define DEFINE_KSPROPERTY_STREAMINTERFACESET(StreamInterfaceSet,HeaderSizeHandler) \
DEFINE_KSPROPERTY_TABLE(StreamInterfaceSet) {               \
    DEFINE_KSPROPERTY_ITEM_STREAMINTERFACE_HEADERSIZE(HeaderSizeHandler)\
}

#define STATIC_KSPROPSETID_Stream                   \
    0x65aaba60L,0x98ae,0x11cf,0xa1,0x0d,0x00,0x20,0xaf,0xd1,0x56,0xe4
DEFINE_GUIDSTRUCT("65aaba60-98ae-11cf-a10d-0020afd156e4", KSPROPSETID_Stream);
#define KSPROPSETID_Stream DEFINE_GUIDNAMED(KSPROPSETID_Stream)

typedef enum {
    KSPROPERTY_STREAM_ALLOCATOR,
    KSPROPERTY_STREAM_QUALITY,
    KSPROPERTY_STREAM_DEGRADATION,
    KSPROPERTY_STREAM_MASTERCLOCK,
    KSPROPERTY_STREAM_TIMEFORMAT,
    KSPROPERTY_STREAM_PRESENTATIONTIME,
    KSPROPERTY_STREAM_PRESENTATIONEXTENT,
    KSPROPERTY_STREAM_FRAMETIME,
    KSPROPERTY_STREAM_RATECAPABILITY,
    KSPROPERTY_STREAM_RATE,
    KSPROPERTY_STREAM_PIPE_ID
} KSPROPERTY_STREAM;

#define DEFINE_KSPROPERTY_ITEM_STREAM_ALLOCATOR(GetHandler,SetHandler)  \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_STREAM_ALLOCATOR,        \
                (GetHandler),               \
                sizeof(KSPROPERTY),         \
                sizeof(HANDLE),             \
                (SetHandler),               \
                NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_STREAM_QUALITY(Handler)          \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_STREAM_QUALITY,      \
                (Handler),              \
                sizeof(KSPROPERTY),         \
                sizeof(KSQUALITY_MANAGER),      \
                NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_STREAM_DEGRADATION(GetHandler,SetHandler)\
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_STREAM_DEGRADATION,      \
                (GetHandler),               \
                sizeof(KSPROPERTY),         \
                0,                  \
                (SetHandler),               \
                NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_STREAM_MASTERCLOCK(GetHandler,SetHandler)\
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_STREAM_MASTERCLOCK,      \
                (GetHandler),               \
                sizeof(KSPROPERTY),         \
                sizeof(HANDLE),             \
                (SetHandler),               \
                NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_STREAM_TIMEFORMAT(Handler)       \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_STREAM_TIMEFORMAT,       \
                (Handler),              \
                sizeof(KSPROPERTY),         \
                sizeof(GUID),               \
                NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_STREAM_PRESENTATIONTIME(GetHandler,SetHandler)\
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_STREAM_PRESENTATIONTIME, \
                (GetHandler),               \
                sizeof(KSPROPERTY),         \
                sizeof(KSTIME),             \
                (SetHandler),               \
                NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_STREAM_PRESENTATIONEXTENT(Handler)   \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_STREAM_PRESENTATIONEXTENT,   \
                (Handler),              \
                sizeof(KSPROPERTY),         \
                sizeof(LONGLONG),           \
                NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_STREAM_FRAMETIME(Handler)        \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_STREAM_FRAMETIME,        \
                (Handler),              \
                sizeof(KSPROPERTY),         \
                sizeof(KSFRAMETIME),            \
                NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_STREAM_RATECAPABILITY(Handler)       \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_STREAM_RATECAPABILITY,   \
                (Handler),              \
                sizeof(KSRATE_CAPABILITY),      \
                sizeof(KSRATE),             \
                NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_STREAM_RATE(GetHandler,SetHandler)   \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_STREAM_RATE,         \
                (GetHandler),               \
                sizeof(KSPROPERTY),         \
                sizeof(KSRATE),             \
                (SetHandler),               \
                NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_STREAM_PIPE_ID(GetHandler,SetHandler)    \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_STREAM_PIPE_ID,      \
                (GetHandler),               \
                sizeof(KSPROPERTY),         \
                sizeof(HANDLE),             \
                (SetHandler),               \
                NULL, 0, NULL, NULL, 0)

typedef struct {
    HANDLE QualityManager;
    PVOID Context;
} KSQUALITY_MANAGER, *PKSQUALITY_MANAGER;

typedef struct {
    LONGLONG Duration;
    ULONG FrameFlags;
    ULONG Reserved;
} KSFRAMETIME, *PKSFRAMETIME;

#define KSFRAMETIME_VARIABLESIZE    0x00000001

typedef struct {
    LONGLONG PresentationStart;
    LONGLONG Duration;
    KSPIN_INTERFACE Interface;
    LONG Rate;
    ULONG Flags;
} KSRATE, *PKSRATE;

#define KSRATE_NOPRESENTATIONSTART  0x00000001
#define KSRATE_NOPRESENTATIONDURATION   0x00000002

typedef struct {
    KSPROPERTY Property;
    KSRATE Rate;
} KSRATE_CAPABILITY, *PKSRATE_CAPABILITY;

#define STATIC_KSPROPSETID_Clock                    \
    0xDF12A4C0L,0xAC17,0x11CF,0xA5,0xD6,0x28,0xDB,0x04,0xC1,0x00,0x00
DEFINE_GUIDSTRUCT("DF12A4C0-AC17-11CF-A5D6-28DB04C10000", KSPROPSETID_Clock);
#define KSPROPSETID_Clock DEFINE_GUIDNAMED(KSPROPSETID_Clock)

#define NANOSECONDS 10000000
#define KSCONVERT_PERFORMANCE_TIME(Frequency,PerformanceTime)       \
    ((((ULONGLONG)(ULONG)(PerformanceTime).HighPart *NANOSECONDS / (Frequency)) << 32) +    \
     ((((((ULONGLONG)(ULONG)(PerformanceTime).HighPart *NANOSECONDS) % (Frequency)) << 32) +\
     ((ULONGLONG)(PerformanceTime).LowPart *NANOSECONDS)) / (Frequency)))

typedef struct {
    ULONG CreateFlags;
} KSCLOCK_CREATE, *PKSCLOCK_CREATE;

typedef struct {
    LONGLONG Time;
    LONGLONG SystemTime;
} KSCORRELATED_TIME, *PKSCORRELATED_TIME;

typedef struct {
    LONGLONG Granularity;
    LONGLONG Error;
} KSRESOLUTION, *PKSRESOLUTION;

typedef enum {
    KSPROPERTY_CLOCK_TIME,
    KSPROPERTY_CLOCK_PHYSICALTIME,
    KSPROPERTY_CLOCK_CORRELATEDTIME,
    KSPROPERTY_CLOCK_CORRELATEDPHYSICALTIME,
    KSPROPERTY_CLOCK_RESOLUTION,
    KSPROPERTY_CLOCK_STATE,
#if defined(_NTDDK_)
    KSPROPERTY_CLOCK_FUNCTIONTABLE
#endif /* #if defined(_NTDDK_) */
} KSPROPERTY_CLOCK;

#if defined(_NTDDK_)
typedef LONGLONG(FASTCALL *PFNKSCLOCK_GETTIME)(PFILE_OBJECT FileObject);
typedef LONGLONG(FASTCALL *PFNKSCLOCK_CORRELATEDTIME)(PFILE_OBJECT FileObject,
                                                      PLONGLONG SystemTime);

typedef struct {
    PFNKSCLOCK_GETTIME GetTime;
    PFNKSCLOCK_GETTIME GetPhysicalTime;
    PFNKSCLOCK_CORRELATEDTIME GetCorrelatedTime;
    PFNKSCLOCK_CORRELATEDTIME GetCorrelatedPhysicalTime;
} KSCLOCK_FUNCTIONTABLE, *PKSCLOCK_FUNCTIONTABLE;

typedef BOOLEAN(*PFNKSSETTIMER)(PVOID Context, PKTIMER Timer,
                                LARGE_INTEGER DueTime, PKDPC Dpc);
typedef BOOLEAN(*PFNKSCANCELTIMER)(PVOID Context, PKTIMER Timer);
typedef LONGLONG(FASTCALL *PFNKSCORRELATEDTIME)(PVOID Context,
                                                PLONGLONG SystemTime);

typedef PVOID           PKSDEFAULTCLOCK;

#define DEFINE_KSPROPERTY_ITEM_CLOCK_TIME(Handler)          \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_CLOCK_TIME,          \
                (Handler),              \
                sizeof(KSPROPERTY), sizeof(LONGLONG),   \
                NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_CLOCK_PHYSICALTIME(Handler)      \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_CLOCK_PHYSICALTIME,      \
                (Handler),              \
                sizeof(KSPROPERTY), sizeof(LONGLONG),   \
                NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_CLOCK_CORRELATEDTIME(Handler)        \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_CLOCK_CORRELATEDTIME,    \
                (Handler),              \
                sizeof(KSPROPERTY),         \
                sizeof(KSCORRELATED_TIME),      \
                NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_CLOCK_CORRELATEDPHYSICALTIME(Handler)    \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_CLOCK_CORRELATEDPHYSICALTIME,\
                (Handler),              \
                sizeof(KSPROPERTY),         \
                sizeof(KSCORRELATED_TIME),      \
                NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_CLOCK_RESOLUTION(Handler)        \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_CLOCK_RESOLUTION,        \
                (Handler),              \
                sizeof(KSPROPERTY),sizeof(KSRESOLUTION),\
                NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_CLOCK_STATE(Handler)         \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_CLOCK_STATE,         \
                (Handler),              \
                sizeof(KSPROPERTY), sizeof(KSSTATE),    \
                NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_ITEM_CLOCK_FUNCTIONTABLE(Handler)     \
    DEFINE_KSPROPERTY_ITEM(                     \
                KSPROPERTY_CLOCK_FUNCTIONTABLE,     \
                (Handler),              \
                sizeof(KSPROPERTY),         \
                sizeof(KSCLOCK_FUNCTIONTABLE),      \
                NULL, NULL, 0, NULL, NULL, 0)

#define DEFINE_KSPROPERTY_CLOCKSET(ClockSet,PropTime,PropPhysicalTime,PropCorrelatedTime,PropCorrelatedPhysicalTime,PropResolution,PropState,PropFunctionTable)\
DEFINE_KSPROPERTY_TABLE(ClockSet) {                 \
    DEFINE_KSPROPERTY_ITEM_CLOCK_TIME(PropTime),            \
    DEFINE_KSPROPERTY_ITEM_CLOCK_PHYSICALTIME(PropPhysicalTime),    \
    DEFINE_KSPROPERTY_ITEM_CLOCK_CORRELATEDTIME(PropCorrelatedTime),\
    DEFINE_KSPROPERTY_ITEM_CLOCK_CORRELATEDPHYSICALTIME(PropCorrelatedPhysicalTime),\
    DEFINE_KSPROPERTY_ITEM_CLOCK_RESOLUTION(PropResolution),    \
    DEFINE_KSPROPERTY_ITEM_CLOCK_STATE(PropState),          \
    DEFINE_KSPROPERTY_ITEM_CLOCK_FUNCTIONTABLE(PropFunctionTable),  \
}
#endif /* #if defined(_NTDDK_) */

#define STATIC_KSEVENTSETID_Clock                   \
    0x364D8E20L,0x62C7,0x11CF,0xA5,0xD6,0x28,0xDB,0x04,0xC1,0x00,0x00
DEFINE_GUIDSTRUCT("364D8E20-62C7-11CF-A5D6-28DB04C10000", KSEVENTSETID_Clock);
#define KSEVENTSETID_Clock DEFINE_GUIDNAMED(KSEVENTSETID_Clock)

typedef enum {
    KSEVENT_CLOCK_INTERVAL_MARK,
    KSEVENT_CLOCK_POSITION_MARK
} KSEVENT_CLOCK_POSITION;

#define STATIC_KSEVENTSETID_Connection                  \
    0x7f4bcbe0L,0x9ea5,0x11cf,0xa5,0xd6,0x28,0xdb,0x04,0xc1,0x00,0x00
DEFINE_GUIDSTRUCT("7f4bcbe0-9ea5-11cf-a5d6-28db04c10000", KSEVENTSETID_Connection);
#define KSEVENTSETID_Connection DEFINE_GUIDNAMED(KSEVENTSETID_Connection)

typedef enum {
    KSEVENT_CONNECTION_POSITIONUPDATE,
    KSEVENT_CONNECTION_DATADISCONTINUITY,
    KSEVENT_CONNECTION_TIMEDISCONTINUITY,
    KSEVENT_CONNECTION_PRIORITY,
    KSEVENT_CONNECTION_ENDOFSTREAM
} KSEVENT_CONNECTION;

typedef struct {
    PVOID Context;
    ULONG Proportion;
    LONGLONG DeltaTime;
} KSQUALITY, *PKSQUALITY;

typedef struct {
    PVOID Context;
    ULONG Status;
} KSERROR, *PKSERROR;

typedef KSIDENTIFIER KSDEGRADE, *PKSDEGRADE;

#define STATIC_KSDEGRADESETID_Standard                  \
    0x9F564180L,0x704C,0x11D0,0xA5,0xD6,0x28,0xDB,0x04,0xC1,0x00,0x00
DEFINE_GUIDSTRUCT("9F564180-704C-11D0-A5D6-28DB04C10000", KSDEGRADESETID_Standard);
#define KSDEGRADESETID_Standard DEFINE_GUIDNAMED(KSDEGRADESETID_Standard)

typedef enum {
    KSDEGRADE_STANDARD_SAMPLE,
    KSDEGRADE_STANDARD_QUALITY,
    KSDEGRADE_STANDARD_COMPUTATION,
    KSDEGRADE_STANDARD_SKIP
} KSDEGRADE_STANDARD;

#if defined(_NTDDK_)

#define KSPROBE_STREAMREAD      0x00000000
#define KSPROBE_STREAMWRITE     0x00000001
#define KSPROBE_ALLOCATEMDL     0x00000010
#define KSPROBE_PROBEANDLOCK        0x00000020
#define KSPROBE_SYSTEMADDRESS       0x00000040
#define KSPROBE_MODIFY          0x00000200
#define KSPROBE_STREAMWRITEMODIFY   (KSPROBE_MODIFY | KSPROBE_STREAMWRITE)
#define KSPROBE_ALLOWFORMATCHANGE   0x00000080
#define KSSTREAM_READ           KSPROBE_STREAMREAD
#define KSSTREAM_WRITE          KSPROBE_STREAMWRITE
#define KSSTREAM_PAGED_DATA     0x00000000
#define KSSTREAM_NONPAGED_DATA      0x00000100
#define KSSTREAM_SYNCHRONOUS        0x00001000
#define KSSTREAM_FAILUREEXCEPTION   0x00002000

typedef NTSTATUS(*PFNKSCONTEXT_DISPATCH)(PVOID Context, PIRP Irp);
typedef NTSTATUS(*PFNKSHANDLER)(PIRP Irp, PKSIDENTIFIER Request, PVOID Data);
typedef BOOLEAN(*PFNKSFASTHANDLER)(PFILE_OBJECT FileObject,
                                   PKSIDENTIFIER Request,
                                   ULONG RequestLength, PVOID Data,
                                   ULONG DataLength,
                                   PIO_STATUS_BLOCK IoStatus);
typedef NTSTATUS(*PFNKSALLOCATOR)(PIRP Irp, ULONG BufferSize,
                                  BOOLEAN InputOperation);

typedef struct {
    KSPROPERTY_MEMBERSHEADER MembersHeader;
    const VOID *Members;
} KSPROPERTY_MEMBERSLIST, *PKSPROPERTY_MEMBERSLIST;

typedef struct {
    KSIDENTIFIER PropTypeSet;
    ULONG MembersListCount;
    const KSPROPERTY_MEMBERSLIST *MembersList;
} KSPROPERTY_VALUES, *PKSPROPERTY_VALUES;

#define DEFINE_KSPROPERTY_TABLE(tablename)              \
    const KSPROPERTY_ITEM tablename[] =

#define DEFINE_KSPROPERTY_ITEM(PropertyId,GetHandler,MinProperty,MinData,SetHandler,Values,RelationsCount,Relations,SupportHandler,SerializedSize)\
{                                   \
            PropertyId, (PFNKSHANDLER)GetHandler,       \
            MinProperty, MinData,               \
            (PFNKSHANDLER)SetHandler,           \
            (PKSPROPERTY_VALUES)Values, RelationsCount, \
            (PKSPROPERTY)Relations,             \
            (PFNKSHANDLER)SupportHandler,           \
            (ULONG)SerializedSize               \
}

typedef struct {
    ULONG PropertyId;
    __MINGW_EXTENSION union {
        PFNKSHANDLER GetPropertyHandler;
        BOOLEAN GetSupported;
    };
    ULONG MinProperty;
    ULONG MinData;
    __MINGW_EXTENSION union {
        PFNKSHANDLER SetPropertyHandler;
        BOOLEAN SetSupported;
    };
    const KSPROPERTY_VALUES *Values;
    ULONG RelationsCount;
    const KSPROPERTY *Relations;
    PFNKSHANDLER SupportHandler;
    ULONG SerializedSize;
} KSPROPERTY_ITEM, *PKSPROPERTY_ITEM;

#define DEFINE_KSFASTPROPERTY_ITEM(PropertyId, GetHandler, SetHandler)  \
{                                   \
            PropertyId, (PFNKSFASTHANDLER)GetHandler,   \
            (PFNKSFASTHANDLER)SetHandler, 0         \
}

typedef struct {
    ULONG PropertyId;
    __MINGW_EXTENSION union {
        PFNKSFASTHANDLER GetPropertyHandler;
        BOOLEAN GetSupported;
    };
    __MINGW_EXTENSION union {
        PFNKSFASTHANDLER SetPropertyHandler;
        BOOLEAN SetSupported;
    };
    ULONG Reserved;
} KSFASTPROPERTY_ITEM, *PKSFASTPROPERTY_ITEM;

#define DEFINE_KSPROPERTY_SET(Set,PropertiesCount,PropertyItem,FastIoCount,FastIoTable)\
{                                   \
            Set,                        \
            PropertiesCount, PropertyItem,          \
            FastIoCount, FastIoTable            \
}

#define DEFINE_KSPROPERTY_SET_TABLE(tablename)              \
    const KSPROPERTY_SET tablename[] =

typedef struct {
    const GUID *Set;
    ULONG PropertiesCount;
    const KSPROPERTY_ITEM *PropertyItem;
    ULONG FastIoCount;
    const KSFASTPROPERTY_ITEM *FastIoTable;
} KSPROPERTY_SET, *PKSPROPERTY_SET;

#define DEFINE_KSMETHOD_TABLE(tablename)                \
    const KSMETHOD_ITEM tablename[] =

#define DEFINE_KSMETHOD_ITEM(MethodId,Flags,MethodHandler,MinMethod,MinData,SupportHandler)\
{                                   \
            MethodId, (PFNKSHANDLER)MethodHandler,      \
            MinMethod, MinData,             \
            SupportHandler, Flags               \
}

typedef struct {
    ULONG MethodId;
    __MINGW_EXTENSION union {
        PFNKSHANDLER MethodHandler;
        BOOLEAN MethodSupported;
    };
    ULONG MinMethod;
    ULONG MinData;
    PFNKSHANDLER SupportHandler;
    ULONG Flags;
} KSMETHOD_ITEM, *PKSMETHOD_ITEM;

#define DEFINE_KSFASTMETHOD_ITEM(MethodId,MethodHandler)        \
{                                   \
            MethodId, (PFNKSFASTHANDLER)MethodHandler   \
}

typedef struct {
    ULONG MethodId;
    __MINGW_EXTENSION union {
        PFNKSFASTHANDLER MethodHandler;
        BOOLEAN MethodSupported;
    };
} KSFASTMETHOD_ITEM, *PKSFASTMETHOD_ITEM;

#define DEFINE_KSMETHOD_SET(Set,MethodsCount,MethodItem,FastIoCount,FastIoTable)\
{                                   \
            Set,                        \
            MethodsCount, MethodItem,           \
            FastIoCount, FastIoTable            \
}

#define DEFINE_KSMETHOD_SET_TABLE(tablename)                \
    const KSMETHOD_SET tablename[] =

typedef struct {
    const GUID *Set;
    ULONG MethodsCount;
    const KSMETHOD_ITEM *MethodItem;
    ULONG FastIoCount;
    const KSFASTMETHOD_ITEM *FastIoTable;
} KSMETHOD_SET, *PKSMETHOD_SET;

typedef struct _KSEVENT_ENTRY   KSEVENT_ENTRY, *PKSEVENT_ENTRY;
typedef NTSTATUS(*PFNKSADDEVENT)(PIRP Irp, PKSEVENTDATA EventData,
                                 struct _KSEVENT_ENTRY *EventEntry);
typedef VOID (*PFNKSREMOVEEVENT)(PFILE_OBJECT FileObject,
                                 struct _KSEVENT_ENTRY *EventEntry);

#define DEFINE_KSEVENT_TABLE(tablename)                 \
    const KSEVENT_ITEM tablename[] =

#define DEFINE_KSEVENT_ITEM(EventId,DataInput,ExtraEntryData,AddHandler,RemoveHandler,SupportHandler)\
{                                   \
            EventId, DataInput, ExtraEntryData,     \
            AddHandler, RemoveHandler, SupportHandler   \
}

typedef struct {
    ULONG EventId;
    ULONG DataInput;
    ULONG ExtraEntryData;
    PFNKSADDEVENT AddHandler;
    PFNKSREMOVEEVENT RemoveHandler;
    PFNKSHANDLER SupportHandler;
} KSEVENT_ITEM, *PKSEVENT_ITEM;

#define DEFINE_KSEVENT_SET(Set,EventsCount,EventItem)           \
{                                   \
            Set, EventsCount, EventItem         \
}

#define DEFINE_KSEVENT_SET_TABLE(tablename)             \
    const KSEVENT_SET tablename[] =

typedef struct {
    const GUID *Set;
    ULONG EventsCount;
    const KSEVENT_ITEM *EventItem;
} KSEVENT_SET, *PKSEVENT_SET;

typedef struct {
    KDPC Dpc;
    ULONG ReferenceCount;
    KSPIN_LOCK AccessLock;
} KSDPC_ITEM, *PKSDPC_ITEM;

typedef struct {
    KSDPC_ITEM DpcItem;
    LIST_ENTRY BufferList;
} KSBUFFER_ITEM, *PKSBUFFER_ITEM;


#define KSEVENT_ENTRY_DELETED       1
#define KSEVENT_ENTRY_ONESHOT       2
#define KSEVENT_ENTRY_BUFFERED      4

struct _KSEVENT_ENTRY {
    LIST_ENTRY ListEntry;
    PVOID Object;
    __MINGW_EXTENSION union {
        PKSDPC_ITEM DpcItem;
        PKSBUFFER_ITEM BufferItem;
    };
    PKSEVENTDATA EventData;
    ULONG NotificationType;
    const KSEVENT_SET *EventSet;
    const KSEVENT_ITEM *EventItem;
    PFILE_OBJECT FileObject;
    ULONG SemaphoreAdjustment;
    ULONG Reserved;
    ULONG Flags;
};

typedef enum {
    KSEVENTS_NONE,
    KSEVENTS_SPINLOCK,
    KSEVENTS_MUTEX,
    KSEVENTS_FMUTEX,
    KSEVENTS_FMUTEXUNSAFE,
    KSEVENTS_INTERRUPT,
    KSEVENTS_ERESOURCE
} KSEVENTS_LOCKTYPE;

#define KSDISPATCH_FASTIO           0x80000000

typedef struct {
    PDRIVER_DISPATCH Create;
    PVOID Context;
    UNICODE_STRING ObjectClass;
    PSECURITY_DESCRIPTOR SecurityDescriptor;
    ULONG Flags;
} KSOBJECT_CREATE_ITEM, *PKSOBJECT_CREATE_ITEM;

typedef VOID (*PFNKSITEMFREECALLBACK)(PKSOBJECT_CREATE_ITEM CreateItem);

#define KSCREATE_ITEM_SECURITYCHANGED       0x00000001
#define KSCREATE_ITEM_WILDCARD          0x00000002
#define KSCREATE_ITEM_NOPARAMETERS      0x00000004
#define KSCREATE_ITEM_FREEONSTOP        0x00000008

#define DEFINE_KSCREATE_DISPATCH_TABLE( tablename )         \
    KSOBJECT_CREATE_ITEM tablename[] =

#define DEFINE_KSCREATE_ITEM(DispatchCreate,TypeName,Context)       \
{                                   \
            (DispatchCreate), (PVOID)(Context),     \
            {                       \
                sizeof(TypeName) - sizeof(UNICODE_NULL),\
                sizeof(TypeName),           \
                (PWCHAR)(TypeName)          \
            },                      \
            NULL, 0                     \
}

#define DEFINE_KSCREATE_ITEMEX(DispatchCreate,TypeName,Context,Flags)   \
{                                   \
            (DispatchCreate),               \
            (PVOID)(Context),               \
            {                       \
                sizeof(TypeName) - sizeof(UNICODE_NULL),\
                sizeof(TypeName),           \
                (PWCHAR)(TypeName)          \
            },                      \
            NULL, (Flags)                   \
}

#define DEFINE_KSCREATE_ITEMNULL(DispatchCreate,Context)        \
{                                   \
            DispatchCreate, Context,            \
            {                       \
                0, 0, NULL,             \
            },                      \
            NULL, 0                     \
}

typedef struct {
    ULONG CreateItemsCount;
    PKSOBJECT_CREATE_ITEM CreateItemsList;
} KSOBJECT_CREATE, *PKSOBJECT_CREATE;

typedef struct {
    PDRIVER_DISPATCH DeviceIoControl;
    PDRIVER_DISPATCH Read;
    PDRIVER_DISPATCH Write;
    PDRIVER_DISPATCH Flush;
    PDRIVER_DISPATCH Close;
    PDRIVER_DISPATCH QuerySecurity;
    PDRIVER_DISPATCH SetSecurity;
    PFAST_IO_DEVICE_CONTROL FastDeviceIoControl;
    PFAST_IO_READ FastRead;
    PFAST_IO_WRITE FastWrite;
} KSDISPATCH_TABLE, *PKSDISPATCH_TABLE;

#define DEFINE_KSDISPATCH_TABLE(tablename,DeviceIoControl,Read,Write,Flush,Close,QuerySecurity,SetSecurity,FastDeviceIoControl,FastRead,FastWrite)\
    const KSDISPATCH_TABLE tablename =              \
    {                               \
        DeviceIoControl,                    \
        Read,                           \
        Write,                          \
        Flush,                          \
        Close,                          \
        QuerySecurity,                      \
        SetSecurity,                        \
        FastDeviceIoControl,                    \
        FastRead,                       \
        FastWrite,                      \
    }

#define KSCREATE_ITEM_IRP_STORAGE(Irp)                  \
    (*(PKSOBJECT_CREATE_ITEM *)&(Irp)->Tail.Overlay.DriverContext[0])
#define KSEVENT_SET_IRP_STORAGE(Irp)                    \
    (*(const KSEVENT_SET **)&(Irp)->Tail.Overlay.DriverContext[0])
#define KSEVENT_ITEM_IRP_STORAGE(Irp)                   \
    (*(const KSEVENT_ITEM **)&(Irp)->Tail.Overlay.DriverContext[3])
#define KSEVENT_ENTRY_IRP_STORAGE(Irp)                  \
    (*(PKSEVENT_ENTRY *)&(Irp)->Tail.Overlay.DriverContext[0])
#define KSMETHOD_SET_IRP_STORAGE(Irp)                   \
    (*(const KSMETHOD_SET **)&(Irp)->Tail.Overlay.DriverContext[0])
#define KSMETHOD_ITEM_IRP_STORAGE(Irp)                  \
    (*(const KSMETHOD_ITEM **)&(Irp)->Tail.Overlay.DriverContext[3])
#define KSMETHOD_TYPE_IRP_STORAGE(Irp)                  \
    (*(ULONG_PTR *)(&(Irp)->Tail.Overlay.DriverContext[2]))
#define KSQUEUE_SPINLOCK_IRP_STORAGE(Irp)               \
    (*(PKSPIN_LOCK *)&(Irp)->Tail.Overlay.DriverContext[1])
#define KSPROPERTY_SET_IRP_STORAGE(Irp)                 \
    (*(const KSPROPERTY_SET **)&(Irp)->Tail.Overlay.DriverContext[0])
#define KSPROPERTY_ITEM_IRP_STORAGE(Irp)                \
    (*(const KSPROPERTY_ITEM **)&(Irp)->Tail.Overlay.DriverContext[3])
#define KSPROPERTY_ATTRIBUTES_IRP_STORAGE(Irp)              \
    (*(PKSATTRIBUTE_LIST *)&(Irp)->Tail.Overlay.DriverContext[2])

typedef PVOID       KSDEVICE_HEADER, KSOBJECT_HEADER;

typedef enum {
    KsInvokeOnSuccess = 1,
    KsInvokeOnError = 2,
    KsInvokeOnCancel = 4
} KSCOMPLETION_INVOCATION;

typedef enum {
    KsListEntryTail,
    KsListEntryHead
} KSLIST_ENTRY_LOCATION;

typedef enum {
    KsAcquireOnly,
    KsAcquireAndRemove,
    KsAcquireOnlySingleItem,
    KsAcquireAndRemoveOnlySingleItem
} KSIRP_REMOVAL_OPERATION;

typedef enum {
    KsStackCopyToNewLocation,
    KsStackReuseCurrentLocation,
    KsStackUseNewLocation
} KSSTACK_USE;

typedef enum {
    KSTARGET_STATE_DISABLED,
    KSTARGET_STATE_ENABLED
} KSTARGET_STATE;

typedef NTSTATUS(*PFNKSIRPLISTCALLBACK)(PIRP Irp, PVOID Context);
typedef VOID (*PFNREFERENCEDEVICEOBJECT)(PVOID Context);
typedef VOID (*PFNDEREFERENCEDEVICEOBJECT)(PVOID Context);
typedef NTSTATUS(*PFNQUERYREFERENCESTRING)(PVOID Context, PWCHAR *String);

#define BUS_INTERFACE_REFERENCE_VERSION         0x100

typedef struct {
    INTERFACE Interface;

    PFNREFERENCEDEVICEOBJECT ReferenceDeviceObject;
    PFNDEREFERENCEDEVICEOBJECT DereferenceDeviceObject;
    PFNQUERYREFERENCESTRING QueryReferenceString;
} BUS_INTERFACE_REFERENCE, *PBUS_INTERFACE_REFERENCE;

#define STATIC_REFERENCE_BUS_INTERFACE      STATIC_KSMEDIUMSETID_Standard
#define REFERENCE_BUS_INTERFACE         KSMEDIUMSETID_Standard

#endif /* #if defined(_NTDDK_) */

#ifndef PACK_PRAGMAS_NOT_SUPPORTED
#include <pshpack1.h>
#endif /* #ifndef PACK_PRAGMAS_NOT_SUPPORTED */

typedef struct {
    GUID PropertySet;
    ULONG Count;
} KSPROPERTY_SERIALHDR, *PKSPROPERTY_SERIALHDR;

#ifndef PACK_PRAGMAS_NOT_SUPPORTED
#include <poppack.h>
#endif /* #ifndef PACK_PRAGMAS_NOT_SUPPORTED */

typedef struct {
    KSIDENTIFIER PropTypeSet;
    ULONG Id;
    ULONG PropertyLength;
} KSPROPERTY_SERIAL, *PKSPROPERTY_SERIAL;


#if defined(_NTDDK_)

#define IOCTL_KS_HANDSHAKE                      \
    CTL_CODE(FILE_DEVICE_KS, 0x007, METHOD_NEITHER, FILE_ANY_ACCESS)

typedef struct {
    GUID ProtocolId;
    PVOID Argument1;
    PVOID Argument2;
} KSHANDSHAKE, *PKSHANDSHAKE;

typedef struct _KSGATE      KSGATE, *PKSGATE;

struct _KSGATE {
    LONG Count;
    PKSGATE NextGate;
};

typedef PVOID KSOBJECT_BAG;


typedef BOOLEAN(*PFNKSGENERATEEVENTCALLBACK)(PVOID Context,
                                             PKSEVENT_ENTRY EventEntry);

typedef NTSTATUS(*PFNKSDEVICECREATE)(PKSDEVICE Device);

typedef NTSTATUS(*PFNKSDEVICEPNPSTART)(PKSDEVICE Device, PIRP Irp,
                                       PCM_RESOURCE_LIST TranslatedResourceList,
                                       PCM_RESOURCE_LIST UntranslatedResourceList);

typedef NTSTATUS(*PFNKSDEVICE)(PKSDEVICE Device);

typedef NTSTATUS(*PFNKSDEVICEIRP)(PKSDEVICE Device, PIRP Irp);

typedef void (*PFNKSDEVICEIRPVOID)(PKSDEVICE Device, PIRP Irp);

typedef NTSTATUS(*PFNKSDEVICEQUERYCAPABILITIES)(PKSDEVICE Device, PIRP Irp,
                                                PDEVICE_CAPABILITIES Capabilities);

typedef NTSTATUS(*PFNKSDEVICEQUERYPOWER)(PKSDEVICE Device, PIRP Irp,
                                         DEVICE_POWER_STATE DeviceTo,
                                         DEVICE_POWER_STATE DeviceFrom,
                                         SYSTEM_POWER_STATE SystemTo,
                                         SYSTEM_POWER_STATE SystemFrom,
                                         POWER_ACTION Action);

typedef void (*PFNKSDEVICESETPOWER)(PKSDEVICE Device, PIRP Irp,
                                    DEVICE_POWER_STATE To,
                                    DEVICE_POWER_STATE From);

typedef NTSTATUS(*PFNKSFILTERFACTORYVOID)(PKSFILTERFACTORY FilterFactory);

typedef void (*PFNKSFILTERFACTORYPOWER)(PKSFILTERFACTORY FilterFactory,
                                        DEVICE_POWER_STATE State);

typedef NTSTATUS(*PFNKSFILTERIRP)(PKSFILTER Filter, PIRP Irp);

typedef NTSTATUS(*PFNKSFILTERPROCESS)(PKSFILTER Filter,
                                      PKSPROCESSPIN_INDEXENTRY Index);

typedef NTSTATUS(*PFNKSFILTERVOID)(PKSFILTER Filter);

typedef void (*PFNKSFILTERPOWER)(PKSFILTER Filter, DEVICE_POWER_STATE State);

typedef NTSTATUS(*PFNKSPINIRP)(PKSPIN Pin, PIRP Irp);

typedef NTSTATUS(*PFNKSPINSETDEVICESTATE)(PKSPIN Pin, KSSTATE ToState,
                                          KSSTATE FromState);

typedef NTSTATUS(*PFNKSPINSETDATAFORMAT)(PKSPIN Pin, PKSDATAFORMAT OldFormat,
                                         PKSMULTIPLE_ITEM OldAttributeList,
                                         const KSDATARANGE *DataRange,
                                         const KSATTRIBUTE_LIST *AttributeRange);

typedef NTSTATUS(*PFNKSPINHANDSHAKE)(PKSPIN Pin, PKSHANDSHAKE In,
                                     PKSHANDSHAKE Out);

typedef NTSTATUS(*PFNKSPIN)(PKSPIN Pin);

typedef void (*PFNKSPINVOID)(PKSPIN Pin);

typedef void (*PFNKSPINPOWER)(PKSPIN Pin, DEVICE_POWER_STATE State);

typedef BOOLEAN(*PFNKSPINSETTIMER)(PKSPIN Pin, PKTIMER Timer,
                                   LARGE_INTEGER DueTime, PKDPC Dpc);

typedef BOOLEAN(*PFNKSPINCANCELTIMER)(PKSPIN Pin, PKTIMER Timer);

typedef LONGLONG(FASTCALL *PFNKSPINCORRELATEDTIME)(PKSPIN Pin,
                                                   PLONGLONG SystemTime);

typedef void (*PFNKSPINRESOLUTION)(PKSPIN Pin, PKSRESOLUTION Resolution);

typedef NTSTATUS(*PFNKSPININITIALIZEALLOCATOR)(PKSPIN Pin,
                                               PKSALLOCATOR_FRAMING AllocatorFraming,
                                               PVOID *Context);

typedef void (*PFNKSSTREAMPOINTER)(PKSSTREAM_POINTER StreamPointer);


typedef struct KSAUTOMATION_TABLE_ KSAUTOMATION_TABLE, *PKSAUTOMATION_TABLE;

struct KSAUTOMATION_TABLE_ {
    ULONG PropertySetsCount;
    ULONG PropertyItemSize;
    const KSPROPERTY_SET *PropertySets;
    ULONG MethodSetsCount;
    ULONG MethodItemSize;
    const KSMETHOD_SET *MethodSets;
    ULONG EventSetsCount;
    ULONG EventItemSize;
    const KSEVENT_SET *EventSets;
#ifndef _WIN64
    PVOID Alignment;
#endif /* #ifndef _WIN64 */
};

#define DEFINE_KSAUTOMATION_TABLE(table)                \
        const KSAUTOMATION_TABLE table =

#define DEFINE_KSAUTOMATION_PROPERTIES(table)               \
        SIZEOF_ARRAY(table),                    \
        sizeof(KSPROPERTY_ITEM),                \
        table

#define DEFINE_KSAUTOMATION_METHODS(table)              \
        SIZEOF_ARRAY(table),                    \
        sizeof(KSMETHOD_ITEM),                  \
        table

#define DEFINE_KSAUTOMATION_EVENTS(table)               \
        SIZEOF_ARRAY(table),                    \
        sizeof(KSEVENT_ITEM),                   \
        table

#define DEFINE_KSAUTOMATION_PROPERTIES_NULL             \
        0,                          \
        sizeof(KSPROPERTY_ITEM),                \
        NULL

#define DEFINE_KSAUTOMATION_METHODS_NULL                \
        0,                          \
        sizeof(KSMETHOD_ITEM),                  \
        NULL

#define DEFINE_KSAUTOMATION_EVENTS_NULL                 \
        0,                          \
        sizeof(KSEVENT_ITEM),                   \
        NULL

#define MIN_DEV_VER_FOR_QI      (0x100)

struct _KSDEVICE_DISPATCH {
    PFNKSDEVICECREATE Add;
    PFNKSDEVICEPNPSTART Start;
    PFNKSDEVICE PostStart;
    PFNKSDEVICEIRP QueryStop;
    PFNKSDEVICEIRPVOID CancelStop;
    PFNKSDEVICEIRPVOID Stop;
    PFNKSDEVICEIRP QueryRemove;
    PFNKSDEVICEIRPVOID CancelRemove;
    PFNKSDEVICEIRPVOID Remove;
    PFNKSDEVICEQUERYCAPABILITIES QueryCapabilities;
    PFNKSDEVICEIRPVOID SurpriseRemoval;
    PFNKSDEVICEQUERYPOWER QueryPower;
    PFNKSDEVICESETPOWER SetPower;
    PFNKSDEVICEIRP QueryInterface;
};

struct _KSFILTER_DISPATCH {
    PFNKSFILTERIRP Create;
    PFNKSFILTERIRP Close;
    PFNKSFILTERPROCESS Process;
    PFNKSFILTERVOID Reset;
};

struct _KSPIN_DISPATCH {
    PFNKSPINIRP Create;
    PFNKSPINIRP Close;
    PFNKSPIN Process;
    PFNKSPINVOID Reset;
    PFNKSPINSETDATAFORMAT SetDataFormat;
    PFNKSPINSETDEVICESTATE SetDeviceState;
    PFNKSPIN Connect;
    PFNKSPINVOID Disconnect;
    const KSCLOCK_DISPATCH *Clock;
    const KSALLOCATOR_DISPATCH *Allocator;
};

struct _KSCLOCK_DISPATCH {
    PFNKSPINSETTIMER SetTimer;
    PFNKSPINCANCELTIMER CancelTimer;
    PFNKSPINCORRELATEDTIME CorrelatedTime;
    PFNKSPINRESOLUTION Resolution;
};

struct _KSALLOCATOR_DISPATCH {
    PFNKSPININITIALIZEALLOCATOR InitializeAllocator;
    PFNKSDELETEALLOCATOR DeleteAllocator;
    PFNKSDEFAULTALLOCATE Allocate;
    PFNKSDEFAULTFREE Free;
};

#define KSDEVICE_DESCRIPTOR_VERSION (0x100)

struct _KSDEVICE_DESCRIPTOR {
    const KSDEVICE_DISPATCH *Dispatch;
    ULONG FilterDescriptorsCount;
    const KSFILTER_DESCRIPTOR *const *FilterDescriptors;
    ULONG Version;
};

struct _KSFILTER_DESCRIPTOR {
    const KSFILTER_DISPATCH *Dispatch;
    const KSAUTOMATION_TABLE *AutomationTable;
    ULONG Version;
#define KSFILTER_DESCRIPTOR_VERSION ((ULONG)-1)
    ULONG Flags;
#define KSFILTER_FLAG_DISPATCH_LEVEL_PROCESSING     0x00000001
#define KSFILTER_FLAG_CRITICAL_PROCESSING       0x00000002
#define KSFILTER_FLAG_HYPERCRITICAL_PROCESSING      0x00000004
#define KSFILTER_FLAG_RECEIVE_ZERO_LENGTH_SAMPLES   0x00000008
#define KSFILTER_FLAG_DENY_USERMODE_ACCESS      0x80000000
    const GUID *ReferenceGuid;
    ULONG PinDescriptorsCount;
    ULONG PinDescriptorSize;
    const KSPIN_DESCRIPTOR_EX *PinDescriptors;
    ULONG CategoriesCount;
    const GUID *Categories;
    ULONG NodeDescriptorsCount;
    ULONG NodeDescriptorSize;
    const KSNODE_DESCRIPTOR *NodeDescriptors;
    ULONG ConnectionsCount;
    const KSTOPOLOGY_CONNECTION *Connections;
    const KSCOMPONENTID *ComponentId;
};

#define DEFINE_KSFILTER_DESCRIPTOR(descriptor)              \
    const KSFILTER_DESCRIPTOR descriptor =

#define DEFINE_KSFILTER_PIN_DESCRIPTORS(table)              \
    SIZEOF_ARRAY(table),                        \
    sizeof(table[0]),                       \
    table

#define DEFINE_KSFILTER_CATEGORIES(table)               \
    SIZEOF_ARRAY(table),                        \
    table

#define DEFINE_KSFILTER_CATEGORY(category)              \
    1,                              \
    &(category)

#define DEFINE_KSFILTER_CATEGORIES_NULL                 \
    0,                              \
    NULL

#define DEFINE_KSFILTER_NODE_DESCRIPTORS(table)             \
    SIZEOF_ARRAY(table),                        \
    sizeof(table[0]),                       \
    table

#define DEFINE_KSFILTER_NODE_DESCRIPTORS_NULL               \
    0,                              \
    sizeof(KSNODE_DESCRIPTOR),                  \
    NULL

#define DEFINE_KSFILTER_CONNECTIONS(table)              \
    SIZEOF_ARRAY(table),                        \
    table

#define DEFINE_KSFILTER_DEFAULT_CONNECTIONS             \
    0,                              \
    NULL

#define DEFINE_KSFILTER_DESCRIPTOR_TABLE(table)             \
    const KSFILTER_DESCRIPTOR*const table[] =

struct _KSPIN_DESCRIPTOR_EX {
    const KSPIN_DISPATCH *Dispatch;
    const KSAUTOMATION_TABLE *AutomationTable;
    KSPIN_DESCRIPTOR PinDescriptor;
    ULONG Flags;
#define KSPIN_FLAG_DISPATCH_LEVEL_PROCESSING    KSFILTER_FLAG_DISPATCH_LEVEL_PROCESSING
#define KSPIN_FLAG_CRITICAL_PROCESSING      KSFILTER_FLAG_CRITICAL_PROCESSING
#define KSPIN_FLAG_HYPERCRITICAL_PROCESSING KSFILTER_FLAG_HYPERCRITICAL_PROCESSING
#define KSPIN_FLAG_ASYNCHRONOUS_PROCESSING          0x00000008
#define KSPIN_FLAG_DO_NOT_INITIATE_PROCESSING           0x00000010
#define KSPIN_FLAG_INITIATE_PROCESSING_ON_EVERY_ARRIVAL     0x00000020
#define KSPIN_FLAG_FRAMES_NOT_REQUIRED_FOR_PROCESSING       0x00000040
#define KSPIN_FLAG_ENFORCE_FIFO                 0x00000080
#define KSPIN_FLAG_GENERATE_MAPPINGS                0x00000100
#define KSPIN_FLAG_DISTINCT_TRAILING_EDGE           0x00000200
#define KSPIN_FLAG_PROCESS_IN_RUN_STATE_ONLY            0x00010000
#define KSPIN_FLAG_SPLITTER                 0x00020000
#define KSPIN_FLAG_USE_STANDARD_TRANSPORT           0x00040000
#define KSPIN_FLAG_DO_NOT_USE_STANDARD_TRANSPORT        0x00080000
#define KSPIN_FLAG_FIXED_FORMAT                 0x00100000
#define KSPIN_FLAG_GENERATE_EOS_EVENTS              0x00200000
#define KSPIN_FLAG_RENDERER         (KSPIN_FLAG_PROCESS_IN_RUN_STATE_ONLY|KSPIN_FLAG_GENERATE_EOS_EVENTS)
#define KSPIN_FLAG_IMPLEMENT_CLOCK              0x00400000
#define KSPIN_FLAG_SOME_FRAMES_REQUIRED_FOR_PROCESSING      0x00800000
#define KSPIN_FLAG_PROCESS_IF_ANY_IN_RUN_STATE          0x01000000
#define KSPIN_FLAG_DENY_USERMODE_ACCESS             0x80000000
    ULONG InstancesPossible;
    ULONG InstancesNecessary;
    const KSALLOCATOR_FRAMING_EX *AllocatorFraming;
    PFNKSINTERSECTHANDLEREX IntersectHandler;
};

#define DEFINE_KSPIN_DEFAULT_INTERFACES                 \
    0,                              \
    NULL

#define DEFINE_KSPIN_DEFAULT_MEDIUMS                    \
    0,                              \
    NULL

struct _KSNODE_DESCRIPTOR {
    const KSAUTOMATION_TABLE *AutomationTable;
    const GUID *Type;
    const GUID *Name;
#ifndef _WIN64
    PVOID Alignment;
#endif /* #ifndef _WIN64 */
};

#ifndef _WIN64
#define DEFINE_NODE_DESCRIPTOR(automation,type,name)            \
    { (automation), (type), (name), NULL }
#else /* #ifndef _WIN64 */
#define DEFINE_NODE_DESCRIPTOR(automation,type,name)            \
    { (automation), (type), (name) }
#endif /* #ifndef _WIN64 */

struct _KSDEVICE {
    const KSDEVICE_DESCRIPTOR *Descriptor;
    KSOBJECT_BAG Bag;
    PVOID Context;
    PDEVICE_OBJECT FunctionalDeviceObject;
    PDEVICE_OBJECT PhysicalDeviceObject;
    PDEVICE_OBJECT NextDeviceObject;
    BOOLEAN Started;
    SYSTEM_POWER_STATE SystemPowerState;
    DEVICE_POWER_STATE DevicePowerState;
};

struct _KSFILTERFACTORY {
    const KSFILTER_DESCRIPTOR *FilterDescriptor;
    KSOBJECT_BAG Bag;
    PVOID Context;
};

struct _KSFILTER {
    const KSFILTER_DESCRIPTOR *Descriptor;
    KSOBJECT_BAG Bag;
    PVOID Context;
};

struct _KSPIN {
    const KSPIN_DESCRIPTOR_EX *Descriptor;
    KSOBJECT_BAG Bag;
    PVOID Context;
    ULONG Id;
    KSPIN_COMMUNICATION Communication;
    BOOLEAN ConnectionIsExternal;
    KSPIN_INTERFACE ConnectionInterface;
    KSPIN_MEDIUM ConnectionMedium;
    KSPRIORITY ConnectionPriority;
    PKSDATAFORMAT ConnectionFormat;
    PKSMULTIPLE_ITEM AttributeList;
    ULONG StreamHeaderSize;
    KSPIN_DATAFLOW DataFlow;
    KSSTATE DeviceState;
    KSRESET ResetState;
    KSSTATE ClientState;
};

struct _KSMAPPING {
    PHYSICAL_ADDRESS PhysicalAddress;
    ULONG ByteCount;
    ULONG Alignment;
};

struct _KSSTREAM_POINTER_OFFSET {
#if defined(_NTDDK_)
    __MINGW_EXTENSION union {
        PUCHAR Data;
        PKSMAPPING Mappings;
    };
#else /* #if defined(_NTDDK_) */
    PUCHAR Data;
#endif /* #if defined(_NTDDK_) */
#ifndef _WIN64
    PVOID Alignment;
#endif /* #ifndef _WIN64 */
    ULONG Count;
    ULONG Remaining;
};

struct _KSSTREAM_POINTER {
    PVOID Context;
    PKSPIN Pin;
    PKSSTREAM_HEADER StreamHeader;
    PKSSTREAM_POINTER_OFFSET Offset;
    KSSTREAM_POINTER_OFFSET OffsetIn;
    KSSTREAM_POINTER_OFFSET OffsetOut;
};

struct _KSPROCESSPIN {
    PKSPIN Pin;
    PKSSTREAM_POINTER StreamPointer;
    PKSPROCESSPIN InPlaceCounterpart;
    PKSPROCESSPIN DelegateBranch;
    PKSPROCESSPIN CopySource;
    PVOID Data;
    ULONG BytesAvailable;
    ULONG BytesUsed;
    ULONG Flags;
    BOOLEAN Terminate;
};

struct _KSPROCESSPIN_INDEXENTRY {
    PKSPROCESSPIN *Pins;
    ULONG Count;
};

typedef enum {
    KsObjectTypeDevice,
    KsObjectTypeFilterFactory,
    KsObjectTypeFilter,
    KsObjectTypePin
} KSOBJECTTYPE;


typedef void (*PFNKSFREE)(PVOID Data);

typedef void (*PFNKSPINFRAMERETURN)(PKSPIN Pin, PVOID Data, ULONG Size, PMDL Mdl,
                                    PVOID Context, NTSTATUS Status);

typedef void (*PFNKSPINIRPCOMPLETION)(PKSPIN Pin, PIRP Irp);


#if defined(_UNKNOWN_H_) || defined(__IUnknown_INTERFACE_DEFINED__)
#ifndef _IKsControl_
#define _IKsControl_

typedef struct IKsControl *PIKSCONTROL;

#ifndef DEFINE_ABSTRACT_UNKNOWN
#define DEFINE_ABSTRACT_UNKNOWN()                   \
    STDMETHOD_(NTSTATUS,QueryInterface) (THIS_          \
                        REFIID InterfaceId, \
                        PVOID *Interface    \
                        ) PURE;         \
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;                \
    STDMETHOD_(ULONG,Release)(THIS) PURE;
#endif /* #ifndef DEFINE_ABSTRACT_UNKNOWN */

#undef INTERFACE
#define INTERFACE IKsControl
DECLARE_INTERFACE_(IKsControl, IUnknown)
{
    DEFINE_ABSTRACT_UNKNOWN()
    STDMETHOD_(NTSTATUS, KsProperty)(THIS_
                                     PKSPROPERTY Property,
                                     ULONG PropertyLength,
                                     PVOID PropertyData,
                                     ULONG DataLength,
                                     ULONG * BytesReturned
                                    ) PURE;
    STDMETHOD_(NTSTATUS, KsMethod)(THIS_
                                   PKSMETHOD Method,
                                   ULONG MethodLength,
                                   PVOID MethodData,
                                   ULONG DataLength,
                                   ULONG * BytesReturned
                                  ) PURE;
    STDMETHOD_(NTSTATUS, KsEvent)(THIS_
                                  PKSEVENT Event,
                                  ULONG EventLength,
                                  PVOID EventData,
                                  ULONG DataLength,
                                  ULONG * BytesReturned
                                 ) PURE;
};
typedef struct IKsReferenceClock *PIKSREFERENCECLOCK;

#undef INTERFACE
#define INTERFACE IKsReferenceClock
DECLARE_INTERFACE_(IKsReferenceClock, IUnknown)
{
    DEFINE_ABSTRACT_UNKNOWN()
    STDMETHOD_(LONGLONG, GetTime)(THIS) PURE;
    STDMETHOD_(LONGLONG, GetPhysicalTime)(THIS) PURE;
    STDMETHOD_(LONGLONG, GetCorrelatedTime)(THIS_
                                            PLONGLONG SystemTime
                                           ) PURE;
    STDMETHOD_(LONGLONG, GetCorrelatedPhysicalTime)(THIS_
                                                    PLONGLONG SystemTime
                                                   ) PURE;
    STDMETHOD_(NTSTATUS, GetResolution)(THIS_
                                        PKSRESOLUTION Resolution
                                       ) PURE;
    STDMETHOD_(NTSTATUS, GetState)(THIS_
                                   PKSSTATE State
                                  ) PURE;
};
#undef INTERFACE

#define INTERFACE IKsDeviceFunctions
DECLARE_INTERFACE_(IKsDeviceFunctions, IUnknown)
{
    DEFINE_ABSTRACT_UNKNOWN()
    STDMETHOD_(NTSTATUS, RegisterAdapterObjectEx)(THIS_
                                                  PADAPTER_OBJECT AdapterObject,
                                                  PDEVICE_DESCRIPTION DeviceDescription,
                                                  ULONG NumberOfMapRegisters,
                                                  ULONG MaxMappingsByteCount,
                                                  ULONG MappingTableStride
                                                 ) PURE;
};

#undef INTERFACE
#define STATIC_IID_IKsControl                       \
    0x28F54685L,0x06FD,0x11D2,0xB2,0x7A,0x00,0xA0,0xC9,0x22,0x31,0x96
DEFINE_GUID(IID_IKsControl,
            0x28F54685L, 0x06FD, 0x11D2, 0xB2, 0x7A, 0x00, 0xA0, 0xC9, 0x22, 0x31, 0x96);
#define STATIC_IID_IKsFastClock                     \
    0xc9902485,0xc180,0x11d2,0x84,0x73,0xd4,0x23,0x94,0x45,0x9e,0x5e
DEFINE_GUID(IID_IKsFastClock,
            0xc9902485, 0xc180, 0x11d2, 0x84, 0x73, 0xd4, 0x23, 0x94, 0x45, 0x9e, 0x5e);
#define STATIC_IID_IKsDeviceFunctions                   \
    0xe234f2e2,0xbd69,0x4f8c,0xb3,0xf2,0x7c,0xd7,0x9e,0xd4,0x66,0xbd
DEFINE_GUID(IID_IKsDeviceFunctions,
            0xe234f2e2, 0xbd69, 0x4f8c, 0xb3, 0xf2, 0x7c, 0xd7, 0x9e, 0xd4, 0x66, 0xbd);
#endif /* #ifndef _IKsControl_ */
#endif /* #if defined(_UNKNOWN_H_) || defined(__IUnknown_INTERFACE_DEFINED__) */

#endif /* #if defined(_NTDDK_) */


#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

#ifdef _KSDDK_
#define KSDDKAPI
#else /* #ifdef _KSDDK_ */
#define KSDDKAPI DECLSPEC_IMPORT
#endif /* #ifdef _KSDDK_ */

#if defined(_NTDDK_)

KSDDKAPI NTSTATUS NTAPI KsEnableEvent
(PIRP Irp, ULONG EventSetsCount, const KSEVENT_SET *EventSet,
 PLIST_ENTRY EventsList, KSEVENTS_LOCKTYPE EventsFlags,
 PVOID EventsLock);

KSDDKAPI NTSTATUS NTAPI KsEnableEventWithAllocator
(PIRP Irp, ULONG EventSetsCount, const KSEVENT_SET *EventSet,
 PLIST_ENTRY EventsList, KSEVENTS_LOCKTYPE EventsFlags,
 PVOID EventsLock, PFNKSALLOCATOR Allocator, ULONG EventItemSize);

KSDDKAPI NTSTATUS NTAPI KsDisableEvent
(PIRP Irp, PLIST_ENTRY EventsList, KSEVENTS_LOCKTYPE EventsFlags,
 PVOID EventsLock);

KSDDKAPI VOID NTAPI KsDiscardEvent(PKSEVENT_ENTRY EventEntry);

KSDDKAPI VOID NTAPI KsFreeEventList
(PFILE_OBJECT FileObject, PLIST_ENTRY EventsList,
 KSEVENTS_LOCKTYPE EventsFlags, PVOID EventsLock);

KSDDKAPI NTSTATUS NTAPI KsGenerateEvent(PKSEVENT_ENTRY EventEntry);

KSDDKAPI NTSTATUS NTAPI KsGenerateDataEvent
(PKSEVENT_ENTRY EventEntry, ULONG DataSize, PVOID Data);

KSDDKAPI VOID NTAPI KsGenerateEventList
(GUID *Set, ULONG EventId, PLIST_ENTRY EventsList,
 KSEVENTS_LOCKTYPE EventsFlags, PVOID EventsLock);

KSDDKAPI NTSTATUS NTAPI KsPropertyHandler
(PIRP Irp, ULONG PropertySetsCount,
 const KSPROPERTY_SET *PropertySet);

KSDDKAPI NTSTATUS NTAPI KsPropertyHandlerWithAllocator
(PIRP Irp, ULONG PropertySetsCount,
 const KSPROPERTY_SET *PropertySet, PFNKSALLOCATOR Allocator,
 ULONG PropertyItemSize);

KSDDKAPI BOOLEAN NTAPI KsFastPropertyHandler
(PFILE_OBJECT FileObject, PKSPROPERTY Property,
 ULONG PropertyLength, PVOID Data, ULONG DataLength,
 PIO_STATUS_BLOCK IoStatus, ULONG PropertySetsCount,
 const KSPROPERTY_SET *PropertySet);

KSDDKAPI NTSTATUS NTAPI KsMethodHandler
(PIRP Irp, ULONG MethodSetsCount,
 const KSMETHOD_SET *MethodSet);

KSDDKAPI NTSTATUS NTAPI KsMethodHandlerWithAllocator
(PIRP Irp, ULONG MethodSetsCount,
 const KSMETHOD_SET *MethodSet, PFNKSALLOCATOR Allocator,
 ULONG MethodItemSize);

KSDDKAPI BOOLEAN NTAPI KsFastMethodHandler
(PFILE_OBJECT FileObject, PKSMETHOD Method, ULONG MethodLength,
 PVOID Data, ULONG DataLength, PIO_STATUS_BLOCK IoStatus,
 ULONG MethodSetsCount, const KSMETHOD_SET *MethodSet);

KSDDKAPI NTSTATUS NTAPI KsCreateDefaultAllocator(PIRP Irp);

KSDDKAPI NTSTATUS NTAPI KsCreateDefaultAllocatorEx
(PIRP Irp, PVOID InitializeContext,
 PFNKSDEFAULTALLOCATE DefaultAllocate,
 PFNKSDEFAULTFREE DefaultFree,
 PFNKSINITIALIZEALLOCATOR InitializeAllocator,
 PFNKSDELETEALLOCATOR DeleteAllocator);

KSDDKAPI NTSTATUS NTAPI KsCreateAllocator
(HANDLE ConnectionHandle, PKSALLOCATOR_FRAMING AllocatorFraming,
 PHANDLE AllocatorHandle);

KSDDKAPI NTSTATUS NTAPI KsValidateAllocatorCreateRequest
(PIRP Irp, PKSALLOCATOR_FRAMING *AllocatorFraming);

KSDDKAPI NTSTATUS NTAPI KsValidateAllocatorFramingEx
(PKSALLOCATOR_FRAMING_EX Framing, ULONG BufferSize,
 const KSALLOCATOR_FRAMING_EX *PinFraming);

KSDDKAPI NTSTATUS NTAPI KsAllocateDefaultClock(PKSDEFAULTCLOCK *DefaultClock);

KSDDKAPI NTSTATUS NTAPI KsAllocateDefaultClockEx
(PKSDEFAULTCLOCK *DefaultClock, PVOID Context,
 PFNKSSETTIMER SetTimer, PFNKSCANCELTIMER CancelTimer,
 PFNKSCORRELATEDTIME CorrelatedTime,
 const KSRESOLUTION *Resolution, ULONG Flags);

KSDDKAPI VOID NTAPI KsFreeDefaultClock(PKSDEFAULTCLOCK DefaultClock);
KSDDKAPI NTSTATUS NTAPI KsCreateDefaultClock(PIRP Irp, PKSDEFAULTCLOCK DefaultClock);

KSDDKAPI NTSTATUS NTAPI KsCreateClock
(HANDLE ConnectionHandle, PKSCLOCK_CREATE ClockCreate,
 PHANDLE ClockHandle);

KSDDKAPI NTSTATUS NTAPI KsValidateClockCreateRequest
(PIRP Irp, PKSCLOCK_CREATE *ClockCreate);

KSDDKAPI KSSTATE NTAPI KsGetDefaultClockState(PKSDEFAULTCLOCK DefaultClock);
KSDDKAPI VOID NTAPI KsSetDefaultClockState(PKSDEFAULTCLOCK DefaultClock, KSSTATE State);
KSDDKAPI LONGLONG NTAPI KsGetDefaultClockTime(PKSDEFAULTCLOCK DefaultClock);
KSDDKAPI VOID NTAPI KsSetDefaultClockTime(PKSDEFAULTCLOCK DefaultClock, LONGLONG Time);

KSDDKAPI NTSTATUS NTAPI KsCreatePin
(HANDLE FilterHandle, PKSPIN_CONNECT Connect,
 ACCESS_MASK DesiredAccess, PHANDLE ConnectionHandle);

KSDDKAPI NTSTATUS NTAPI KsValidateConnectRequest
(PIRP Irp, ULONG DescriptorsCount,
 const KSPIN_DESCRIPTOR *Descriptor, PKSPIN_CONNECT *Connect);

KSDDKAPI NTSTATUS NTAPI KsPinPropertyHandler
(PIRP Irp, PKSPROPERTY Property, PVOID Data,
 ULONG DescriptorsCount, const KSPIN_DESCRIPTOR *Descriptor);

KSDDKAPI NTSTATUS NTAPI KsPinDataIntersection
(PIRP Irp, PKSP_PIN Pin, PVOID Data, ULONG DescriptorsCount,
 const KSPIN_DESCRIPTOR *Descriptor,
 PFNKSINTERSECTHANDLER IntersectHandler);

KSDDKAPI NTSTATUS NTAPI KsPinDataIntersectionEx
(PIRP Irp, PKSP_PIN Pin, PVOID Data, ULONG DescriptorsCount,
 const KSPIN_DESCRIPTOR *Descriptor, ULONG DescriptorSize,
 PFNKSINTERSECTHANDLEREX IntersectHandler, PVOID HandlerContext);

KSDDKAPI NTSTATUS NTAPI KsHandleSizedListQuery
(PIRP Irp, ULONG DataItemsCount, ULONG DataItemSize,
 const VOID *DataItems);

#ifndef MAKEINTRESOURCE
#define MAKEINTRESOURCE(r)      ((ULONG_PTR) (USHORT) r)
#endif /* #ifndef MAKEINTRESOURCE */
#ifndef RT_STRING
#define RT_STRING           MAKEINTRESOURCE(6)
#define RT_RCDATA           MAKEINTRESOURCE(10)
#endif /* #ifndef RT_STRING */

KSDDKAPI NTSTATUS NTAPI KsLoadResource
(PVOID ImageBase, POOL_TYPE PoolType, ULONG_PTR ResourceName,
 ULONG ResourceType, PVOID *Resource, PULONG ResourceSize);

KSDDKAPI NTSTATUS NTAPI KsGetImageNameAndResourceId
(HANDLE RegKey, PUNICODE_STRING ImageName, PULONG_PTR ResourceId,
 PULONG ValueType);

KSDDKAPI NTSTATUS NTAPI KsMapModuleName
(PDEVICE_OBJECT PhysicalDeviceObject, PUNICODE_STRING ModuleName,
 PUNICODE_STRING ImageName, PULONG_PTR ResourceId,
 PULONG ValueType);

KSDDKAPI NTSTATUS NTAPI KsReferenceBusObject(KSDEVICE_HEADER Header);
KSDDKAPI VOID NTAPI KsDereferenceBusObject(KSDEVICE_HEADER Header);
KSDDKAPI NTSTATUS NTAPI KsDispatchQuerySecurity(PDEVICE_OBJECT DeviceObject, PIRP Irp);
KSDDKAPI NTSTATUS NTAPI KsDispatchSetSecurity(PDEVICE_OBJECT DeviceObject, PIRP Irp);
KSDDKAPI NTSTATUS NTAPI KsDispatchSpecificProperty(PIRP Irp, PFNKSHANDLER Handler);
KSDDKAPI NTSTATUS NTAPI KsDispatchSpecificMethod(PIRP Irp, PFNKSHANDLER Handler);

KSDDKAPI NTSTATUS NTAPI KsReadFile
(PFILE_OBJECT FileObject, PKEVENT Event, PVOID PortContext,
 PIO_STATUS_BLOCK IoStatusBlock, PVOID Buffer, ULONG Length,
 ULONG Key, KPROCESSOR_MODE RequestorMode);

KSDDKAPI NTSTATUS NTAPI KsWriteFile
(PFILE_OBJECT FileObject, PKEVENT Event, PVOID PortContext,
 PIO_STATUS_BLOCK IoStatusBlock, PVOID Buffer, ULONG Length,
 ULONG Key, KPROCESSOR_MODE RequestorMode);

KSDDKAPI NTSTATUS NTAPI KsQueryInformationFile
(PFILE_OBJECT FileObject, PVOID FileInformation, ULONG Length,
 FILE_INFORMATION_CLASS FileInformationClass);

KSDDKAPI NTSTATUS NTAPI KsSetInformationFile
(PFILE_OBJECT FileObject, PVOID FileInformation, ULONG Length,
 FILE_INFORMATION_CLASS FileInformationClass);

KSDDKAPI NTSTATUS NTAPI KsStreamIo
(PFILE_OBJECT FileObject, PKEVENT Event, PVOID PortContext,
 PIO_COMPLETION_ROUTINE CompletionRoutine, PVOID CompletionContext,
 KSCOMPLETION_INVOCATION CompletionInvocationFlags,
 PIO_STATUS_BLOCK IoStatusBlock, PVOID StreamHeaders, ULONG Length,
 ULONG Flags, KPROCESSOR_MODE RequestorMode);

KSDDKAPI NTSTATUS NTAPI KsProbeStreamIrp(PIRP Irp, ULONG ProbeFlags, ULONG HeaderSize);
KSDDKAPI NTSTATUS NTAPI KsAllocateExtraData(PIRP Irp, ULONG ExtraSize, PVOID *ExtraBuffer);
KSDDKAPI VOID NTAPI KsNullDriverUnload(PDRIVER_OBJECT DriverObject);

KSDDKAPI NTSTATUS NTAPI KsSetMajorFunctionHandler
(PDRIVER_OBJECT DriverObject, ULONG MajorFunction);

KSDDKAPI NTSTATUS NTAPI KsDispatchInvalidDeviceRequest
(PDEVICE_OBJECT DeviceObject, PIRP Irp);

KSDDKAPI NTSTATUS NTAPI KsDefaultDeviceIoCompletion
(PDEVICE_OBJECT DeviceObject, PIRP Irp);

KSDDKAPI NTSTATUS NTAPI KsDispatchIrp(PDEVICE_OBJECT DeviceObject, PIRP Irp);

KSDDKAPI BOOLEAN NTAPI KsDispatchFastIoDeviceControlFailure
(PFILE_OBJECT FileObject, BOOLEAN Wait, PVOID InputBuffer,
 ULONG InputBufferLength, PVOID OutputBuffer,
 ULONG OutputBufferLength, ULONG IoControlCode,
 PIO_STATUS_BLOCK IoStatus, PDEVICE_OBJECT DeviceObject);

KSDDKAPI BOOLEAN NTAPI KsDispatchFastReadFailure
(PFILE_OBJECT FileObject, PLARGE_INTEGER FileOffset,
 ULONG Length, BOOLEAN Wait, ULONG LockKey, PVOID Buffer,
 PIO_STATUS_BLOCK IoStatus, PDEVICE_OBJECT DeviceObject);

#define KsDispatchFastWriteFailure      KsDispatchFastReadFailure

KSDDKAPI VOID NTAPI KsCancelRoutine(PDEVICE_OBJECT DeviceObject, PIRP Irp);
KSDDKAPI VOID NTAPI KsCancelIo(PLIST_ENTRY QueueHead, PKSPIN_LOCK SpinLock);
KSDDKAPI VOID NTAPI KsReleaseIrpOnCancelableQueue(PIRP Irp, PDRIVER_CANCEL DriverCancel);

KSDDKAPI PIRP NTAPI KsRemoveIrpFromCancelableQueue
(PLIST_ENTRY QueueHead, PKSPIN_LOCK SpinLock,
 KSLIST_ENTRY_LOCATION ListLocation,
 KSIRP_REMOVAL_OPERATION RemovalOperation);

KSDDKAPI NTSTATUS NTAPI KsMoveIrpsOnCancelableQueue
(PLIST_ENTRY SourceList, PKSPIN_LOCK SourceLock,
 PLIST_ENTRY DestinationList, PKSPIN_LOCK DestinationLock,
 KSLIST_ENTRY_LOCATION ListLocation,
 PFNKSIRPLISTCALLBACK ListCallback, PVOID Context);

KSDDKAPI VOID NTAPI KsRemoveSpecificIrpFromCancelableQueue(PIRP Irp);

KSDDKAPI VOID NTAPI KsAddIrpToCancelableQueue
(PLIST_ENTRY QueueHead, PKSPIN_LOCK SpinLock, PIRP Irp,
 KSLIST_ENTRY_LOCATION ListLocation, PDRIVER_CANCEL DriverCancel);

KSDDKAPI NTSTATUS NTAPI KsAcquireResetValue(PIRP Irp, KSRESET *ResetValue);

KSDDKAPI NTSTATUS NTAPI KsTopologyPropertyHandler
(PIRP Irp, PKSPROPERTY Property, PVOID Data,
 const KSTOPOLOGY *Topology);

KSDDKAPI VOID NTAPI KsAcquireDeviceSecurityLock(KSDEVICE_HEADER Header, BOOLEAN Exclusive);
KSDDKAPI VOID NTAPI KsReleaseDeviceSecurityLock(KSDEVICE_HEADER Header);
KSDDKAPI NTSTATUS NTAPI KsDefaultDispatchPnp(PDEVICE_OBJECT DeviceObject, PIRP Irp);
KSDDKAPI NTSTATUS NTAPI KsDefaultDispatchPower(PDEVICE_OBJECT DeviceObject, PIRP Irp);
KSDDKAPI NTSTATUS NTAPI KsDefaultForwardIrp(PDEVICE_OBJECT DeviceObject, PIRP Irp);

KSDDKAPI VOID NTAPI KsSetDevicePnpAndBaseObject
(KSDEVICE_HEADER Header, PDEVICE_OBJECT PnpDeviceObject,
 PDEVICE_OBJECT BaseObject);

KSDDKAPI PDEVICE_OBJECT NTAPI KsQueryDevicePnpObject(KSDEVICE_HEADER Header);
KSDDKAPI ACCESS_MASK NTAPI KsQueryObjectAccessMask(KSOBJECT_HEADER Header);

KSDDKAPI VOID NTAPI KsRecalculateStackDepth
(KSDEVICE_HEADER Header, BOOLEAN ReuseStackLocation);

KSDDKAPI VOID NTAPI KsSetTargetState
(KSOBJECT_HEADER Header, KSTARGET_STATE TargetState);

KSDDKAPI VOID NTAPI KsSetTargetDeviceObject
(KSOBJECT_HEADER Header, PDEVICE_OBJECT TargetDevice);

KSDDKAPI VOID NTAPI KsSetPowerDispatch
(KSOBJECT_HEADER Header, PFNKSCONTEXT_DISPATCH PowerDispatch,
 PVOID PowerContext);

KSDDKAPI PKSOBJECT_CREATE_ITEM NTAPI KsQueryObjectCreateItem(KSOBJECT_HEADER Header);

KSDDKAPI NTSTATUS NTAPI KsAllocateDeviceHeader
(KSDEVICE_HEADER *Header, ULONG ItemsCount,
 PKSOBJECT_CREATE_ITEM ItemsList);

KSDDKAPI VOID NTAPI KsFreeDeviceHeader(KSDEVICE_HEADER Header);

KSDDKAPI NTSTATUS NTAPI KsAllocateObjectHeader
(KSOBJECT_HEADER *Header, ULONG ItemsCount,
 PKSOBJECT_CREATE_ITEM ItemsList, PIRP Irp,
 const KSDISPATCH_TABLE *Table);

KSDDKAPI VOID NTAPI KsFreeObjectHeader(KSOBJECT_HEADER Header);

KSDDKAPI NTSTATUS NTAPI KsAddObjectCreateItemToDeviceHeader
(KSDEVICE_HEADER Header, PDRIVER_DISPATCH Create, PVOID Context,
 PWSTR ObjectClass, PSECURITY_DESCRIPTOR SecurityDescriptor);

KSDDKAPI NTSTATUS NTAPI KsAddObjectCreateItemToObjectHeader
(KSOBJECT_HEADER Header, PDRIVER_DISPATCH Create, PVOID Context,
 PWSTR ObjectClass, PSECURITY_DESCRIPTOR SecurityDescriptor);

KSDDKAPI NTSTATUS NTAPI KsAllocateObjectCreateItem
(KSDEVICE_HEADER Header, PKSOBJECT_CREATE_ITEM CreateItem,
 BOOLEAN AllocateEntry, PFNKSITEMFREECALLBACK ItemFreeCallback);

KSDDKAPI NTSTATUS NTAPI KsFreeObjectCreateItem
(KSDEVICE_HEADER Header, PUNICODE_STRING CreateItem);

KSDDKAPI NTSTATUS NTAPI KsFreeObjectCreateItemsByContext
(KSDEVICE_HEADER Header, PVOID Context);

KSDDKAPI NTSTATUS NTAPI KsCreateDefaultSecurity
(PSECURITY_DESCRIPTOR ParentSecurity,
 PSECURITY_DESCRIPTOR *DefaultSecurity);

KSDDKAPI NTSTATUS NTAPI KsForwardIrp
(PIRP Irp, PFILE_OBJECT FileObject, BOOLEAN ReuseStackLocation);

KSDDKAPI NTSTATUS NTAPI KsForwardAndCatchIrp
(PDEVICE_OBJECT DeviceObject, PIRP Irp, PFILE_OBJECT FileObject,
 KSSTACK_USE StackUse);

KSDDKAPI NTSTATUS NTAPI KsSynchronousIoControlDevice
(PFILE_OBJECT FileObject, KPROCESSOR_MODE RequestorMode,
 ULONG IoControl, PVOID InBuffer, ULONG InSize, PVOID OutBuffer,
 ULONG OutSize, PULONG BytesReturned);

KSDDKAPI NTSTATUS NTAPI KsUnserializeObjectPropertiesFromRegistry
(PFILE_OBJECT FileObject, HANDLE ParentKey,
 PUNICODE_STRING RegistryPath);

KSDDKAPI NTSTATUS NTAPI KsCacheMedium
(PUNICODE_STRING SymbolicLink, PKSPIN_MEDIUM Medium,
 ULONG PinDirection);

KSDDKAPI NTSTATUS NTAPI KsRegisterWorker
(WORK_QUEUE_TYPE WorkQueueType, PKSWORKER *Worker);

KSDDKAPI NTSTATUS NTAPI KsRegisterCountedWorker
(WORK_QUEUE_TYPE WorkQueueType, PWORK_QUEUE_ITEM CountedWorkItem,
 PKSWORKER *Worker);

KSDDKAPI VOID NTAPI KsUnregisterWorker(PKSWORKER Worker);
KSDDKAPI NTSTATUS NTAPI KsQueueWorkItem(PKSWORKER Worker, PWORK_QUEUE_ITEM WorkItem);
KSDDKAPI ULONG NTAPI KsIncrementCountedWorker(PKSWORKER Worker);
KSDDKAPI ULONG NTAPI KsDecrementCountedWorker(PKSWORKER Worker);

KSDDKAPI NTSTATUS NTAPI KsCreateTopologyNode
(HANDLE ParentHandle, PKSNODE_CREATE NodeCreate,
 ACCESS_MASK DesiredAccess, PHANDLE NodeHandle);

KSDDKAPI NTSTATUS NTAPI KsValidateTopologyNodeCreateRequest
(PIRP Irp, PKSTOPOLOGY Topology, PKSNODE_CREATE *NodeCreate);

KSDDKAPI NTSTATUS NTAPI KsMergeAutomationTables
(PKSAUTOMATION_TABLE *AutomationTableAB,
 PKSAUTOMATION_TABLE AutomationTableA,
 PKSAUTOMATION_TABLE AutomationTableB,
 KSOBJECT_BAG Bag);

KSDDKAPI NTSTATUS NTAPI KsInitializeDriver
(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPathName,
 const KSDEVICE_DESCRIPTOR *Descriptor);

KSDDKAPI NTSTATUS NTAPI KsAddDevice
(PDRIVER_OBJECT DriverObject, PDEVICE_OBJECT PhysicalDeviceObject);

KSDDKAPI NTSTATUS NTAPI KsCreateDevice
(PDRIVER_OBJECT DriverObject, PDEVICE_OBJECT PhysicalDeviceObject,
 const KSDEVICE_DESCRIPTOR *Descriptor, ULONG ExtensionSize,
 PKSDEVICE *Device);

KSDDKAPI NTSTATUS NTAPI KsInitializeDevice
(PDEVICE_OBJECT FunctionalDeviceObject,
 PDEVICE_OBJECT PhysicalDeviceObject,
 PDEVICE_OBJECT NextDeviceObject,
 const KSDEVICE_DESCRIPTOR *Descriptor);

KSDDKAPI void NTAPI KsTerminateDevice(PDEVICE_OBJECT DeviceObject);
KSDDKAPI PKSDEVICE NTAPI KsGetDeviceForDeviceObject(PDEVICE_OBJECT FunctionalDeviceObject);
KSDDKAPI void NTAPI KsAcquireDevice(PKSDEVICE Device);
KSDDKAPI void NTAPI KsReleaseDevice(PKSDEVICE Device);

KSDDKAPI void NTAPI KsDeviceRegisterAdapterObject
(PKSDEVICE Device, PADAPTER_OBJECT AdapterObject,
 ULONG MaxMappingsByteCount, ULONG MappingTableStride);

KSDDKAPI ULONG NTAPI KsDeviceGetBusData
(PKSDEVICE Device, ULONG DataType, PVOID Buffer, ULONG Offset,
 ULONG Length);

KSDDKAPI ULONG NTAPI KsDeviceSetBusData
(PKSDEVICE Device, ULONG DataType, PVOID Buffer, ULONG Offset,
 ULONG Length);

KSDDKAPI NTSTATUS NTAPI KsCreateFilterFactory
(PDEVICE_OBJECT DeviceObject, const KSFILTER_DESCRIPTOR *Descriptor,
 PWSTR RefString, PSECURITY_DESCRIPTOR SecurityDescriptor,
 ULONG CreateItemFlags, PFNKSFILTERFACTORYPOWER SleepCallback,
 PFNKSFILTERFACTORYPOWER WakeCallback,
 PKSFILTERFACTORY *FilterFactory);

#define KsDeleteFilterFactory(FilterFactory)                                                \
    KsFreeObjectCreateItemsByContext( *(KSDEVICE_HEADER *)(                                     \
                        KsFilterFactoryGetParentDevice(FilterFactory)->FunctionalDeviceObject->DeviceExtension),\
                       FilterFactory)

KSDDKAPI NTSTATUS NTAPI KsFilterFactoryUpdateCacheData
(PKSFILTERFACTORY FilterFactory,
 const KSFILTER_DESCRIPTOR *FilterDescriptor);

KSDDKAPI NTSTATUS NTAPI KsFilterFactoryAddCreateItem
(PKSFILTERFACTORY FilterFactory, PWSTR RefString,
 PSECURITY_DESCRIPTOR SecurityDescriptor, ULONG CreateItemFlags);

KSDDKAPI NTSTATUS NTAPI KsFilterFactorySetDeviceClassesState
(PKSFILTERFACTORY FilterFactory, BOOLEAN NewState);

KSDDKAPI PUNICODE_STRING NTAPI KsFilterFactoryGetSymbolicLink
(PKSFILTERFACTORY FilterFactory);

KSDDKAPI void NTAPI KsAddEvent(PVOID Object, PKSEVENT_ENTRY EventEntry);

void __forceinline KsFilterAddEvent(PKSFILTER Filter, PKSEVENT_ENTRY EventEntry)
{
    KsAddEvent(Filter, EventEntry);
}

void __forceinline KsPinAddEvent(PKSPIN Pin, PKSEVENT_ENTRY EventEntry)
{
    KsAddEvent(Pin, EventEntry);
}

KSDDKAPI NTSTATUS NTAPI KsDefaultAddEventHandler
(PIRP Irp, PKSEVENTDATA EventData, PKSEVENT_ENTRY EventEntry);

KSDDKAPI void NTAPI KsGenerateEvents
(PVOID Object, const GUID *EventSet, ULONG EventId,
 ULONG DataSize, PVOID Data, PFNKSGENERATEEVENTCALLBACK CallBack,
 PVOID CallBackContext);

void __forceinline KsFilterGenerateEvents
(PKSFILTER Filter, const GUID *EventSet, ULONG EventId,
 ULONG DataSize, PVOID Data, PFNKSGENERATEEVENTCALLBACK CallBack,
 PVOID CallBackContext)
{
    KsGenerateEvents(Filter, EventSet, EventId, DataSize, Data, CallBack,
                     CallBackContext);
}

void __forceinline KsPinGenerateEvents
(PKSPIN Pin, const GUID *EventSet, ULONG EventId,
 ULONG DataSize, PVOID Data, PFNKSGENERATEEVENTCALLBACK CallBack,
 PVOID CallBackContext)
{
    KsGenerateEvents(Pin, EventSet, EventId, DataSize, Data, CallBack,
                     CallBackContext);
}

typedef enum {
    KSSTREAM_POINTER_STATE_UNLOCKED = 0,
    KSSTREAM_POINTER_STATE_LOCKED
} KSSTREAM_POINTER_STATE;

KSDDKAPI NTSTATUS NTAPI KsPinGetAvailableByteCount
(PKSPIN Pin, PLONG InputDataBytes, PLONG OutputBufferBytes);

KSDDKAPI PKSSTREAM_POINTER NTAPI KsPinGetLeadingEdgeStreamPointer
(PKSPIN Pin, KSSTREAM_POINTER_STATE State);

KSDDKAPI PKSSTREAM_POINTER NTAPI KsPinGetTrailingEdgeStreamPointer
(PKSPIN Pin, KSSTREAM_POINTER_STATE State);

KSDDKAPI NTSTATUS NTAPI KsStreamPointerSetStatusCode
(PKSSTREAM_POINTER StreamPointer, NTSTATUS Status);

KSDDKAPI NTSTATUS NTAPI KsStreamPointerLock(PKSSTREAM_POINTER StreamPointer);
KSDDKAPI void NTAPI KsStreamPointerUnlock(PKSSTREAM_POINTER StreamPointer, BOOLEAN Eject);

KSDDKAPI void NTAPI KsStreamPointerAdvanceOffsetsAndUnlock
(PKSSTREAM_POINTER StreamPointer, ULONG InUsed, ULONG OutUsed,
 BOOLEAN Eject);

KSDDKAPI void NTAPI KsStreamPointerDelete(PKSSTREAM_POINTER StreamPointer);

KSDDKAPI NTSTATUS NTAPI KsStreamPointerClone
(PKSSTREAM_POINTER StreamPointer, PFNKSSTREAMPOINTER CancelCallback,
 ULONG ContextSize, PKSSTREAM_POINTER *CloneStreamPointer);

KSDDKAPI NTSTATUS NTAPI KsStreamPointerAdvanceOffsets
(PKSSTREAM_POINTER StreamPointer, ULONG InUsed, ULONG OutUsed,
 BOOLEAN Eject);

KSDDKAPI NTSTATUS NTAPI KsStreamPointerAdvance(PKSSTREAM_POINTER StreamPointer);
KSDDKAPI PMDL NTAPI KsStreamPointerGetMdl(PKSSTREAM_POINTER StreamPointer);

KSDDKAPI PIRP NTAPI KsStreamPointerGetIrp
(PKSSTREAM_POINTER StreamPointer, PBOOLEAN FirstFrameInIrp,
 PBOOLEAN LastFrameInIrp);

KSDDKAPI void NTAPI KsStreamPointerScheduleTimeout
(PKSSTREAM_POINTER StreamPointer, PFNKSSTREAMPOINTER Callback,
 ULONGLONG Interval);

KSDDKAPI void NTAPI KsStreamPointerCancelTimeout(PKSSTREAM_POINTER StreamPointer);
KSDDKAPI PKSSTREAM_POINTER NTAPI KsPinGetFirstCloneStreamPointer(PKSPIN Pin);

KSDDKAPI PKSSTREAM_POINTER NTAPI KsStreamPointerGetNextClone
(PKSSTREAM_POINTER StreamPointer);

KSDDKAPI NTSTATUS NTAPI KsPinHandshake(PKSPIN Pin, PKSHANDSHAKE In, PKSHANDSHAKE Out);
KSDDKAPI void NTAPI KsCompletePendingRequest(PIRP Irp);
KSDDKAPI KSOBJECTTYPE NTAPI KsGetObjectTypeFromIrp(PIRP Irp);
KSDDKAPI PVOID NTAPI KsGetObjectFromFileObject(PFILE_OBJECT FileObject);
KSDDKAPI KSOBJECTTYPE NTAPI KsGetObjectTypeFromFileObject(PFILE_OBJECT FileObject);

PKSFILTER __forceinline KsGetFilterFromFileObject(PFILE_OBJECT FileObject)
{
    return (PKSFILTER) KsGetObjectFromFileObject(FileObject);
}

PKSPIN __forceinline KsGetPinFromFileObject(PFILE_OBJECT FileObject)
{
    return (PKSPIN) KsGetObjectFromFileObject(FileObject);
}

KSDDKAPI PKSGATE NTAPI KsFilterGetAndGate(PKSFILTER Filter);
KSDDKAPI void NTAPI KsFilterAcquireProcessingMutex(PKSFILTER Filter);
KSDDKAPI void NTAPI KsFilterReleaseProcessingMutex(PKSFILTER Filter);
KSDDKAPI void NTAPI KsFilterAttemptProcessing(PKSFILTER Filter, BOOLEAN Asynchronous);
KSDDKAPI PKSGATE NTAPI KsPinGetAndGate(PKSPIN Pin);
KSDDKAPI void NTAPI KsPinAttachAndGate(PKSPIN Pin, PKSGATE AndGate);
KSDDKAPI void NTAPI KsPinAttachOrGate(PKSPIN Pin, PKSGATE OrGate);
KSDDKAPI void NTAPI KsPinAcquireProcessingMutex(PKSPIN Pin);
KSDDKAPI void NTAPI KsPinReleaseProcessingMutex(PKSPIN Pin);
KSDDKAPI BOOLEAN NTAPI KsProcessPinUpdate(PKSPROCESSPIN ProcessPin);

KSDDKAPI void NTAPI KsPinGetCopyRelationships
(PKSPIN Pin, PKSPIN *CopySource, PKSPIN *DelegateBranch);

KSDDKAPI void NTAPI KsPinAttemptProcessing(PKSPIN Pin, BOOLEAN Asynchronous);
KSDDKAPI PVOID NTAPI KsGetParent(PVOID Object);

PKSDEVICE __forceinline KsFilterFactoryGetParentDevice(PKSFILTERFACTORY FilterFactory)
{
    return (PKSDEVICE) KsGetParent((PVOID) FilterFactory);
}

PKSFILTERFACTORY __forceinline KsFilterGetParentFilterFactory(PKSFILTER Filter)
{
    return (PKSFILTERFACTORY) KsGetParent((PVOID) Filter);
}

KSDDKAPI PKSFILTER NTAPI KsPinGetParentFilter(PKSPIN Pin);
KSDDKAPI PVOID NTAPI KsGetFirstChild(PVOID Object);

PKSFILTERFACTORY __forceinline KsDeviceGetFirstChildFilterFactory(PKSDEVICE Device)
{
    return (PKSFILTERFACTORY) KsGetFirstChild((PVOID) Device);
}

PKSFILTER __forceinline KsFilterFactoryGetFirstChildFilter(PKSFILTERFACTORY FilterFactory)
{
    return (PKSFILTER) KsGetFirstChild((PVOID) FilterFactory);
}

KSDDKAPI ULONG NTAPI KsFilterGetChildPinCount(PKSFILTER Filter, ULONG PinId);
KSDDKAPI PKSPIN NTAPI KsFilterGetFirstChildPin(PKSFILTER Filter, ULONG PinId);
KSDDKAPI PVOID NTAPI KsGetNextSibling(PVOID Object);
KSDDKAPI PKSPIN NTAPI KsPinGetNextSiblingPin(PKSPIN Pin);

PKSFILTERFACTORY __forceinline KsFilterFactoryGetNextSiblingFilterFactory
(PKSFILTERFACTORY FilterFactory)
{
    return (PKSFILTERFACTORY) KsGetNextSibling((PVOID) FilterFactory);
}

PKSFILTER __forceinline KsFilterGetNextSiblingFilter(PKSFILTER Filter)
{
    return (PKSFILTER) KsGetNextSibling((PVOID) Filter);
}

KSDDKAPI PKSDEVICE NTAPI KsGetDevice(PVOID Object);

PKSDEVICE __forceinline KsFilterFactoryGetDevice(PKSFILTERFACTORY FilterFactory)
{
    return KsGetDevice((PVOID) FilterFactory);
}

PKSDEVICE __forceinline KsFilterGetDevice(PKSFILTER Filter)
{
    return KsGetDevice((PVOID) Filter);
}

PKSDEVICE __forceinline KsPinGetDevice(PKSPIN Pin)
{
    return KsGetDevice((PVOID) Pin);
}

KSDDKAPI PKSFILTER NTAPI KsGetFilterFromIrp(PIRP Irp);
KSDDKAPI PKSPIN NTAPI KsGetPinFromIrp(PIRP Irp);
KSDDKAPI ULONG NTAPI KsGetNodeIdFromIrp(PIRP Irp);
KSDDKAPI void NTAPI KsAcquireControl(PVOID Object);
KSDDKAPI void NTAPI KsReleaseControl(PVOID Object);

void __forceinline KsFilterAcquireControl(PKSFILTER Filter)
{
    KsAcquireControl((PVOID) Filter);
}

void __forceinline KsFilterReleaseControl(PKSFILTER Filter)
{
    KsReleaseControl((PVOID) Filter);
}

void __forceinline KsPinAcquireControl(PKSPIN Pin)
{
    KsAcquireControl((PVOID) Pin);
}

void __forceinline KsPinReleaseControl(PKSPIN Pin)
{
    KsReleaseControl((PVOID) Pin);
}

KSDDKAPI NTSTATUS NTAPI KsAddItemToObjectBag
(KSOBJECT_BAG ObjectBag, PVOID Item, PFNKSFREE Free);

KSDDKAPI ULONG NTAPI KsRemoveItemFromObjectBag
(KSOBJECT_BAG ObjectBag, PVOID Item, BOOLEAN Free);

#define KsDiscard(Object,Pointer)                   \
    KsRemoveItemFromObjectBag((Object)->Bag, (PVOID)(Pointer), TRUE)

KSDDKAPI NTSTATUS NTAPI KsAllocateObjectBag(PKSDEVICE Device, KSOBJECT_BAG *ObjectBag);
KSDDKAPI void NTAPI KsFreeObjectBag(KSOBJECT_BAG ObjectBag);

KSDDKAPI NTSTATUS NTAPI KsCopyObjectBagItems
(KSOBJECT_BAG ObjectBagDestination, KSOBJECT_BAG ObjectBagSource);

KSDDKAPI NTSTATUS NTAPI _KsEdit
(KSOBJECT_BAG ObjectBag, PVOID *PointerToPointerToItem,
 ULONG NewSize, ULONG OldSize, ULONG Tag);

#define KsEdit(Object, PointerToPointer, Tag)                       \
    _KsEdit((Object)->Bag, (PVOID*)(PointerToPointer),              \
        sizeof(**(PointerToPointer)), sizeof(**(PointerToPointer)), (Tag))

#define KsEditSized(Object, PointerToPointer, NewSize, OldSize, Tag)            \
    _KsEdit((Object)->Bag, (PVOID*)(PointerToPointer), (NewSize), (OldSize), (Tag))

KSDDKAPI NTSTATUS NTAPI KsRegisterFilterWithNoKSPins
(PDEVICE_OBJECT DeviceObject, const GUID *InterfaceClassGUID,
 ULONG PinCount, WINBOOL *PinDirection, KSPIN_MEDIUM *MediumList,
 GUID *CategoryList);

KSDDKAPI NTSTATUS NTAPI KsFilterCreatePinFactory
(PKSFILTER Filter, const KSPIN_DESCRIPTOR_EX *const PinDescriptor,
 PULONG PinID);

KSDDKAPI NTSTATUS NTAPI KsFilterCreateNode
(PKSFILTER Filter, const KSNODE_DESCRIPTOR *const NodeDescriptor,
 PULONG NodeID);

KSDDKAPI NTSTATUS NTAPI KsFilterAddTopologyConnections
(PKSFILTER Filter, ULONG NewConnectionsCount,
 const KSTOPOLOGY_CONNECTION *const NewTopologyConnections);

KSDDKAPI NTSTATUS NTAPI KsPinGetConnectedPinInterface
(PKSPIN Pin, const GUID *InterfaceId, PVOID *Interface);

KSDDKAPI PFILE_OBJECT NTAPI KsPinGetConnectedPinFileObject(PKSPIN Pin);
KSDDKAPI PDEVICE_OBJECT NTAPI KsPinGetConnectedPinDeviceObject(PKSPIN Pin);

KSDDKAPI NTSTATUS NTAPI KsPinGetConnectedFilterInterface
(PKSPIN Pin, const GUID *InterfaceId, PVOID *Interface);

#if defined(_UNKNOWN_H_) || defined(__IUnknown_INTERFACE_DEFINED__)
KSDDKAPI NTSTATUS NTAPI KsPinGetReferenceClockInterface
(PKSPIN Pin, PIKSREFERENCECLOCK *Interface);
#endif /* #if defined(_UNKNOWN_H_) || defined(__IUnknown_INTERFACE_DEFINED__) */

KSDDKAPI VOID NTAPI KsPinSetPinClockTime(PKSPIN Pin, LONGLONG Time);

KSDDKAPI NTSTATUS NTAPI KsPinSubmitFrame
(PKSPIN Pin, PVOID Data, ULONG Size,
 PKSSTREAM_HEADER StreamHeader, PVOID Context);

KSDDKAPI NTSTATUS NTAPI KsPinSubmitFrameMdl
(PKSPIN Pin, PMDL Mdl, PKSSTREAM_HEADER StreamHeader,
 PVOID Context);

KSDDKAPI void NTAPI KsPinRegisterFrameReturnCallback
(PKSPIN Pin, PFNKSPINFRAMERETURN FrameReturn);

KSDDKAPI void NTAPI KsPinRegisterIrpCompletionCallback
(PKSPIN Pin, PFNKSPINIRPCOMPLETION IrpCompletion);

KSDDKAPI void NTAPI KsPinRegisterHandshakeCallback
(PKSPIN Pin, PFNKSPINHANDSHAKE Handshake);

KSDDKAPI void NTAPI KsFilterRegisterPowerCallbacks
(PKSFILTER Filter, PFNKSFILTERPOWER Sleep, PFNKSFILTERPOWER Wake);

KSDDKAPI void NTAPI KsPinRegisterPowerCallbacks
(PKSPIN Pin, PFNKSPINPOWER Sleep, PFNKSPINPOWER Wake);

#if defined(_UNKNOWN_H_) || defined(__IUnknown_INTERFACE_DEFINED__)
KSDDKAPI PUNKNOWN NTAPI KsRegisterAggregatedClientUnknown
(PVOID Object, PUNKNOWN ClientUnknown);

KSDDKAPI PUNKNOWN NTAPI KsGetOuterUnknown(PVOID Object);

PUNKNOWN __forceinline KsDeviceRegisterAggregatedClientUnknown
(PKSDEVICE Device, PUNKNOWN ClientUnknown)
{
    return KsRegisterAggregatedClientUnknown((PVOID)Device, ClientUnknown);
}

PUNKNOWN __forceinline KsDeviceGetOuterUnknown(PKSDEVICE Device)
{
    return KsGetOuterUnknown((PVOID) Device);
}

PUNKNOWN __forceinline KsFilterFactoryRegisterAggregatedClientUnknown
(PKSFILTERFACTORY FilterFactory, PUNKNOWN ClientUnknown)
{
    return KsRegisterAggregatedClientUnknown((PVOID)FilterFactory, ClientUnknown);
}

PUNKNOWN __forceinline KsFilterFactoryGetOuterUnknown(PKSFILTERFACTORY FilterFactory)
{
    return KsGetOuterUnknown((PVOID)FilterFactory);
}

PUNKNOWN __forceinline KsFilterRegisterAggregatedClientUnknown
(PKSFILTER Filter, PUNKNOWN ClientUnknown)
{
    return KsRegisterAggregatedClientUnknown((PVOID)Filter, ClientUnknown);
}

PUNKNOWN __forceinline KsFilterGetOuterUnknown(PKSFILTER Filter)
{
    return KsGetOuterUnknown((PVOID)Filter);
}

PUNKNOWN __forceinline KsPinRegisterAggregatedClientUnknown
(PKSPIN Pin, PUNKNOWN ClientUnknown)
{
    return KsRegisterAggregatedClientUnknown((PVOID)Pin, ClientUnknown);
}

PUNKNOWN __forceinline KsPinGetOuterUnknown(PKSPIN Pin)
{
    return KsGetOuterUnknown((PVOID)Pin);
}
#endif /* #if defined(_UNKNOWN_H_) || defined(__IUnknown_INTERFACE_DEFINED__) */

#else /* #if defined(_NTDDK_) */

#ifndef KS_NO_CREATE_FUNCTIONS
KSDDKAPI DWORD WINAPI KsCreateAllocator(HANDLE ConnectionHandle, PKSALLOCATOR_FRAMING AllocatorFraming, PHANDLE AllocatorHandle);
KSDDKAPI DWORD NTAPI KsCreateClock(HANDLE ConnectionHandle, PKSCLOCK_CREATE ClockCreate, PHANDLE ClockHandle);
KSDDKAPI DWORD WINAPI KsCreatePin(HANDLE FilterHandle, PKSPIN_CONNECT Connect, ACCESS_MASK DesiredAccess, PHANDLE ConnectionHandle);
KSDDKAPI DWORD WINAPI KsCreateTopologyNode(HANDLE ParentHandle, PKSNODE_CREATE NodeCreate, ACCESS_MASK DesiredAccess, PHANDLE NodeHandle);
#endif /* #ifndef KS_NO_CREATE_FUNCTIONS */

#endif /* #if defined(_NTDDK_) */

#ifdef __cplusplus
}
#endif /* #ifdef __cplusplus */

#define DENY_USERMODE_ACCESS(pIrp,CompleteRequest)          \
    if(pIrp->RequestorMode!=KernelMode) {               \
        pIrp->IoStatus.Information = 0;             \
        pIrp->IoStatus.Status = STATUS_INVALID_DEVICE_REQUEST;  \
        if(CompleteRequest)                 \
            IoCompleteRequest (pIrp,IO_NO_INCREMENT);   \
        return STATUS_INVALID_DEVICE_REQUEST;           \
    }

#endif /* #ifndef _KS_ */

