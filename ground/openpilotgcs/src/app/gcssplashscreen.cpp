/**
 ******************************************************************************
 *
 * @file       gcssplashscreen.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2012.
 * @addtogroup [Group]
 * @{
 * @addtogroup GCSSplashScreen
 * @{
 * @brief [Brief]
 *****************************************************************************/
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "gcssplashscreen.h"
#include <QDebug>

const QChar CopyrightSymbol(0x00a9);

GCSSplashScreen::GCSSplashScreen() :
    QSplashScreen(), m_pixmap(0), m_painter(0)
{
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    m_pixmap = new QPixmap(":/app/splash.png");

    m_painter = new QPainter(m_pixmap);
    m_painter->setPen(Qt::lightGray);
    QFont font("Tahoma", 8);
    m_painter->setFont(font);
    m_painter->drawText(405, 170, QString(CopyrightSymbol) +
                     QString(tr("2010-2013 The OpenPilot Project - All Rights Reserved")));
    QString revision;

#ifdef GCS_REVISION
    revision = GCS_REVISION;
#else
    revision = tr("N/A");
#endif

    m_painter->drawText(405, 190, QString(tr("GCS Revision - ")) + revision);
    setPixmap(*m_pixmap);
}

GCSSplashScreen::~GCSSplashScreen()
{
}

void GCSSplashScreen::drawMessageText(const QString &message)
{
    QPixmap pix(*m_pixmap);
    QPainter progressPainter(&pix);
    progressPainter.setPen(Qt::lightGray);
    QFont font("Tahoma", 13);
    progressPainter.setFont(font);
    progressPainter.drawText(170, 385, message);
    setPixmap(pix);
}

void GCSSplashScreen::showPluginLoadingProgress(ExtensionSystem::PluginSpec *pluginSpec)
{    
    QString message(tr("Loading ") + pluginSpec->name() + " plugin...");
    drawMessageText(message);
}
