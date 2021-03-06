# Created by: dpejesh@yahoo.com
# $FreeBSD$

PORTNAME=	crmsh
PORTVERSION=	2.2.0
PORTREVISION=	2
CATEGORIES=	net-mgmt python

MAINTAINER=	dpejesh@yahoo.com
COMMENT=	Command-line interface for High-Availability cluster management

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/COPYING

RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}lxml>0:devel/py-lxml \
		${PYTHON_PKGNAMEPREFIX}yaml>0:devel/py-yaml

USE_GITHUB=	yes
GH_ACCOUNT=	ClusterLabs

USES=		autoreconf gmake python:2 shebangfix
GNU_CONFIGURE=	yes
CONFIGURE_ARGS=	--with-ocf-root=${PREFIX}/etc/ocf
NO_ARCH=	yes

SHEBANG_FILES=	crm \
		test/cib-tests.sh \
		utils/crm_pkg.py \
		utils/crm_rpmcheck.py

OPTIONS_DEFINE=	DOCS MANPAGES
OPTIONS_DEFAULT=MANPAGES
OPTIONS_SUB=	yes

DOCS_BUILD_DEPENDS=	asciidoc:textproc/asciidoc

MANPAGES_BUILD_DEPENDS=	${DOCS_BUILD_DEPENDS}

post-install:
	${MV} ${STAGEDIR}${PREFIX}/etc/crm/crm.conf \
		${STAGEDIR}${PREFIX}/etc/crm/crm.conf.sample

.include <bsd.port.mk>
