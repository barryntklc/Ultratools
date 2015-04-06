/****************************************************************************
**
** Author & Contact: Quentin BRAMAS ( contact@bramas.fr )
**
** This file is part of Ultratools.
**
** GNU General Public License Usage
** ExUlt is free software: you can redistribute it and/or modify it under the
** terms of General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.txt included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** ExUlt is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** If you have questions regarding the use of this file, please contact
** Quentin BRAMAS (contact@bramas.fr).
**
****************************************************************************/


#include <QApplication>
#include <QTranslator>
#include <QMessageBox>

#include "editorwindow.h"
#include <QInputDialog>
#include <QDir>
#include <QFileInfo>

void setLang(QApplication& app, const QString& idl){
        qWarning(QString("Lang is %1 (lang_%1)").arg(idl).toLatin1());

        QTranslator* translator = new QTranslator();
        translator->load("UltraTools_Editor_" + idl,":/lang");
        app.installTranslator(translator);
}


void manageLang(QApplication& app){
        QSettings settings;
        int lang = settings.value("lang", -1).toInt();
        if( lang == -1){
                QStringList languages;
                languages << "English" << "Francais" << "Spanish(not finished)";
                lang = languages.indexOf(QInputDialog::getItem(0, "Preference", "Choose your language ?", languages, 0, false));
                if(lang == -1){
                        lang = 0;
                }
                settings.setValue("lang", lang);
        }

        switch(lang){
                case 0:
                        setLang(app,"en");
                        break;
                case 1:
                        setLang(app,"fr");
                        break;
                case 2:
                                setLang(app,"en");
                                break;
        }
}


int main(int argc, char *argv[])
{

#ifdef __APPLE__
     QDir dir(QFileInfo(argv[0]).path());  // e.g. appdir/Contents/MacOS
     dir.cdUp();
     if(dir.cd("PlugIns"))// e.g. appdir/Contents/PlugIns
     {
        QApplication::setLibraryPaths( QStringList(dir.absolutePath()));
     }
     else
     {
         qDebug()<<"undeployed";
     }
#endif
#ifdef _WIN32
     QDir dir(QFileInfo(argv[0]).path());  // e.g. appdir/Contents/MacOS
     if(dir.cd("PlugIns"))// e.g. appdir/PlugIns
     {
        QApplication::setLibraryPaths( QStringList(dir.absolutePath()));
     }
     else
     {
         qDebug()<<"undeployed";
     }
#endif

    QApplication a(argc, argv);
    a.setOrganizationName("Ultratools");
    a.setOrganizationDomain("ultratools.org");
    a.setApplicationName("Editor");
    qDebug()<<"Ultratools Editor "VERSION;

    manageLang(a);

    UEditorWindow w;
    w.show();


    return a.exec();
}
