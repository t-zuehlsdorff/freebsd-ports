# Created by: mathias.picker@gmx.de
# $FreeBSD$

PORTNAME=	sooperlooper
PORTVERSION=	1.7.3
PORTREVISION=	2
CATEGORIES=	audio
MASTER_SITES=	http://essej.net/sooperlooper/

MAINTAINER=	ports@FreeBSD.org
COMMENT=	Live audio looping sampler

LICENSE=	GPLv2

BUILD_DEPENDS=	ladspa>0:audio/ladspa
LIB_DEPENDS=	libjack.so:audio/jack \
		liblo.so:audio/liblo \
		libsamplerate.so:audio/libsamplerate \
		libsigc-2.0.so:devel/libsigc++20 \
		libsndfile.so:audio/libsndfile \
		librubberband.so:audio/rubberband \
		libvamp-sdk.so:audio/vamp-plugin-sdk \
		libfftw3.so:math/fftw3
RUN_DEPENDS=	ladspa>0:audio/ladspa

BROKEN_FreeBSD_9=	does not build

USES=		gmake localbase ncurses pkgconfig
USE_GNOME=	libxml2
GNU_CONFIGURE=	yes
USE_LDCONFIG=	yes

CFLAGS+=	-Wno-error=write-strings

OPTIONS_DEFINE=		ALSA WXGTK
OPTIONS_DEFAULT=	WXGTK
OPTIONS_SUB=		yes

ALSA_LIB_DEPENDS=	libasound.so:audio/alsa-lib
ALSA_CONFIGURE_ENV_OFF=	ac_cv_header_alsa_asoundlib_h=no
WXGTK_USE=		WX=3.0
WXGTK_CONFIGURE_ON=	--with-wxconfig-path=${WX_CONFIG}
WXGTK_CONFIGURE_OFF=	--without-gui
WXGTK_DESKTOP_ENTRIES=	"SooperLooper" "" "${DATADIR}/sl_logo.xpm" "slgui" \
			"AudioVideo;Audio;Player;GTK;" ""

post-patch:
	@${FIND} ${WRKSRC} -name "configure" | ${XARGS} ${REINPLACE_CMD} -e \
		's|$$OPT_FLAGS|$$CXXFLAGS| ; \
		 /^CXXFLAGS/s|-g|$$CXXFLAGS| ; \
		 s|-fo-merge-constants||'

post-install-WXGTK-on:
	${INSTALL_DATA} ${WRKSRC}/src/gui/pixmaps/sl_logo.xpm ${STAGEDIR}${DATADIR}

.include <bsd.port.mk>
