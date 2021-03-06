# Created by: Thomas E. Zander with help from Vladimir Kushnir
# $FreeBSD$

PORTNAME=	mplayer
PORTVERSION=	${MPLAYER_PORT_VERSION}.${MPLAYER_SNAPSHOT_DATE:S/-//g}
CATEGORIES=	multimedia audio

MAINTAINER=	riggs@FreeBSD.org
COMMENT=	High performance media player supporting many formats

.include "${.CURDIR}/../../multimedia/mplayer/Makefile.common"

OPTIONS_DEFINE=	AALIB AMR_NB AMR_WB BLURAY CACA CDIO DEBUG DV DVDNAV \
		ENCA FONTCONFIG FRIBIDI GIF GNUTLS GSM GUI IPV6 JACK \
		LADSPA LIBMNG LIRC LZO NAS OCFLAGS OPENAL OPENGL \
		OPENJPEG OPUS PULSEAUDIO RTC RTMP \
		SCHROEDINGER SDL SKINS SMB SPEEX SVGALIB V4L VDPAU VPX \
		X11 X11DGA X11VM XINERAMA XVIDEO XVMC

OPTIONS_DEFAULT=DVDNAV FONTCONFIG FRIBIDI GNUTLS OCFLAGS OPENGL \
		SKINS X11 X11DGA X11VM XINERAMA XVIDEO

OPTIONS_DEFINE_i386=	RTCPU
OPTIONS_DEFINE_amd64=	RTCPU
OPTIONS_DEFINE_powerpc=	RTCPU

OPTIONS_DEFAULT_i386=	RTCPU VDPAU
OPTIONS_DEFAULT_amd64=	RTCPU VDPAU
OPTIONS_DEFAULT_powerpc=RTCPU

DVDNAV_DESC?=	DVD navigation features support
BLURAY_DESC?=	BluRay support
ENCA_DESC?=	Charset conversion via enca
LZO_DESC?=	External liblzo support
OCFLAGS_DESC?=	${OPTIMIZED_CFLAGS_DESC}
RTC_DESC?=	Add support for kernel real time clock
RTCPU_DESC?=	Use runtime CPU detection
SKINS_DESC?=	Install skins for GUI
X11DGA_DESC?=	X11 DGA video driver support
X11VM_DESC?=	X11 VidMode support

SUB_FILES=	pkg-message

CONFLICTS=	mplayer2-2.*

CONFFILES=	example.conf input.conf menu.conf dvb-menu.conf
USES+=		iconv pkgconfig

.include "${.CURDIR}/../../multimedia/mplayer/Makefile.optvars"
.include <bsd.port.options.mk>

CONFIGURE_ARGS+=	--disable-arts \
			--disable-directfb \
			--disable-faac \
			--disable-libdca \
			--disable-toolame \
			--disable-twolame \
			--disable-x264 \
			--disable-xvid \
			--disable-libdirac-lavc \
			--disable-mencoder \
			--disable-mpg123 \
			--disable-musepack \
			--disable-theora

.if ${PORT_OPTIONS:MGUI} && ${PORT_OPTIONS:MX11}
PLIST_SUB+=	GMPLAYER=""
DESKTOP_ENTRIES=	"MPlayer" "High performance media player" "mplayer" "gmplayer" "" false
.if ${PORT_OPTIONS:MSKINS}
RUN_DEPENDS+=	mplayer-skins>=0:multimedia/mplayer-skins
.endif

USE_GNOME+=	gtk20
CONFIGURE_ARGS+=	--enable-gui

.else
PLIST_SUB+=	GMPLAYER="@comment "
.endif #GUI && X11

.if ${PORT_OPTIONS:MX11}
USE_XORG=	x11 xext xproto xscrnsaver
.if ${PORT_OPTIONS:MXVIDEO}
USE_XORG+=	xv
.else
CONFIGURE_ARGS+=--disable-xv
.endif
.if ${PORT_OPTIONS:MX11DGA}
USE_XORG+=	xxf86dga
.else
CONFIGURE_ARGS+=--disable-dga1 --disable-dga2
.endif
.if ${PORT_OPTIONS:MOPENGL}
USE_GL+=	gl
.else
CONFIGURE_ARGS+=--disable-gl
.endif
.if ${PORT_OPTIONS:MXINERAMA}
USE_XORG+=	xinerama xineramaproto
.else
CONFIGURE_ARGS+=--disable-xinerama
.endif
.if ${PORT_OPTIONS:MX11VM}
USE_XORG+=	xxf86vm
.else
CONFIGURE_ARGS+=--disable-vm
.endif
.if ${PORT_OPTIONS:MXVMC}
USE_XORG+=	xvmc
CONFIGURE_ARGS+=--enable-xvmc --with-xvmclib=XvMCW
.endif
.else	#X11
CONFIGURE_ARGS+=--disable-x11
.endif

.include <bsd.port.pre.mk>
.include "${.CURDIR}/../../multimedia/mplayer/Makefile.options"

BROKEN_armv6=		Fails to compile: Error: garbage following instruction -- vmov s16,SCALE
BROKEN_aarch64=		Fails to compile: error: invalid operand for instruction

pre-everything::
	@${ECHO_MSG} "N - O - T - E"
	@${ECHO_MSG} ""
	@${ECHO_MSG} "There are some knobs which *can* *not* be selected via the"
	@${ECHO_MSG} "OPTIONS framework. At the moment, these settings are:"
	@${ECHO_MSG} "WITH_KERN_HZ=${DEFAULT_KERN_HZ}"
	@${ECHO_MSG} "DEFAULT_DVD_DEVICE=${DEFAULT_DVD_DEVICE}"
	@${ECHO_MSG} "DEFAULT_CDROM_DEVICE=${DEFAULT_CDROM_DEVICE}"

.if ${PORT_OPTIONS:MGUI} && ${PORT_OPTIONS:MX11}
	@${ECHO_MSG} "If you want to use the GUI, you can use the skins from"
	@${ECHO_MSG} "${PORTSDIR}/multimedia/mplayer-skins"
	@${ECHO_MSG} "or download them from"
	@${ECHO_MSG} "http://www.mplayerhq.hu/"
.endif

post-patch:
	@${REINPLACE_CMD} \
		-e 's|/dev/dvd|${DEFAULT_DVD_DEVICE}|; \
		s|/dev/cdrom|${DEFAULT_CDROM_DEVICE}|' \
		-e 's|/usr/local|${LOCALBASE}|' \
		-e 's|%%LOCALBASE%%|${LOCALBASE}|' \
		-e 's|-lbz2|/usr/lib/libbz2.so|' \
		-e 's|-lncurses|/usr/lib/libncurses.so|' \
		-e 's|-liconv|${ICONV_LIB}|' \
		${CONFIGURE_WRKSRC}/${CONFIGURE_SCRIPT}
	@${FIND} -E ${WRKSRC} -type f \
		-iregex ".*(configure|.sh|Makefile)" -print0 | \
		${XARGS} -x -0 -n 10 \
		${REINPLACE_CMD} -E \
			-e 's|[[:space:]]gcc[-[:digit:]\.]+| ${CC}|' \
			-e 's|[[:space:]]gcc| ${CC}|' \
			-e 's|\$$\(CC\)|${CC}|' \
			-e 's|/usr/X11R6|${LOCALBASE}|' \
			-e 's|%%LOCALBASE%%|${LOCALBASE}|'
	@${FIND} ${WRKSRC}/DOCS/man -name "mplayer.1" | ${XARGS} ${REINPLACE_CMD} -E -e \
		's|/usr/\\:local/\\:etc/\\:mplayer|${DATADIR:S/\//\/\\\:/g}|g ; \
		 s|/dev/\\:(dvd[[:alnum:]]*[[:>:]])|${DEFAULT_DVD_DEVICE:S/dev\//dev\/\\\:/}|g ; \
		 s|/dev/\\:(cdrom[[:alnum:]]*[[:>:]])|${DEFAULT_CDROM_DEVICE:S/dev\//dev\/\\\:/}|g'

post-patch-RTC-on:
	@${REINPLACE_CMD} -e 's|irqp = 1024|irqp = ${DEFAULT_KERN_HZ}|' ${WRKSRC}/mplayer.c

post-install:
	@${MKDIR} ${STAGEDIR}${DATADIR}
	@${CHMOD} 755 ${STAGEDIR}${DATADIR}
	@${MKDIR} ${STAGEDIR}${DATADIR}/examples/etc
	@${CHMOD} 755 ${STAGEDIR}${DATADIR}/examples/etc
.for conf in ${CONFFILES}
	${INSTALL_DATA} ${WRKSRC}/etc/${conf} ${STAGEDIR}${DATADIR}/examples/etc
.endfor
.if ${PORT_OPTIONS:MGUI} && ${PORT_OPTIONS:MX11}
	@${LN} -sf mplayer ${STAGEDIR}${PREFIX}/bin/gmplayer
	@(cd ${STAGEDIR}${MAN1PREFIX}/man/man1 && ${LN} -sf mplayer.1.gz gmplayer.1.gz)
	${CP} -f ${WRKSRC}/etc/mplayer256x256.png ${STAGEDIR}${PREFIX}/share/pixmaps/mplayer.png
.endif

.include <bsd.port.post.mk>
