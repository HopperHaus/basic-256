/** Copyright (C) 2010, J.M.Reneau
 **
 **  This program is free software; you can redistribute it and/or modify
 **  it under the terms of the GNU General Public License as published by
 **  the Free Software Foundation; either version 2 of the License, or
 **  (at your option) any later version.
 **
 **  This program is distributed in the hope that it will be useful,
 **  but WITHOUT ANY WARRANTY; without even the implied warranty of
 **  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 **  GNU General Public License for more details.
 **
 **  You should have received a copy of the GNU General Public License along
 **  with this program; if not, write to the Free Software Foundation, Inc.,
 **  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 **/

using namespace std;

#include "ReplaceWin.h"
#include "Settings.h"
#include "MainWindow.h"

extern BasicEdit * editwin;
extern MainWindow * mainwin;

ReplaceWin::ReplaceWin () {
    replaceMode = true;

    // position where it was last on screen
    SETTINGS;
    move(settings.value(SETTINGSREPLACEPOS, QPoint(200, 200)).toPoint());

    QGridLayout * layout = new QGridLayout();
    int r=0;
    //
    findLabel = new QLabel(tr("Find:"),this);
    layout->addWidget(findLabel,r,1,1,1);
    findText = new QLineEdit;
    findText->setMaxLength(100);
    findText->setClearButtonEnabled(true);
    connect(findText, SIGNAL(textChanged(QString)), this, SLOT (changeFindText(QString)));
    layout->addWidget(findText,r,2,1,3);
    //
    r++;
    replaceLabel = new QLabel(tr("Replace with:"),this);
    layout->addWidget(replaceLabel,r,1,1,1);
    replaceText = new QLineEdit;
    replaceText->setMaxLength(100);
    replaceText->setClearButtonEnabled(true);
    layout->addWidget(replaceText,r,2,1,3);
    //
    r++;
    caseCheckbox = new QCheckBox(tr("Case sensitive"),this);
    layout->addWidget(caseCheckbox,r,2,1,3);
    //
    r++;
    wordsCheckbox = new QCheckBox(tr("Only whole words"),this);
    layout->addWidget(wordsCheckbox,r,2,1,3);
    //
    r++;
    backCheckbox = new QCheckBox(tr("Search backwards"),this);
    layout->addWidget(backCheckbox,r,2,1,3);
    //
    r++;
    findButton = new QPushButton(tr("&Find"), this);
    connect(findButton, SIGNAL(clicked()), this, SLOT (clickFindButton()));
    layout->addWidget(findButton,r,1,1,1);
    replaceButton = new QPushButton(tr("&Replace"), this);
    connect(replaceButton, SIGNAL(clicked()), this, SLOT (clickReplaceButton()));
    layout->addWidget(replaceButton,r,2,1,1);
    replaceAllButton = new QPushButton(tr("Replace &All"), this);
    connect(replaceAllButton, SIGNAL(clicked()), this, SLOT (clickReplaceAllButton()));
    layout->addWidget(replaceAllButton,r,3,1,1);
    cancelButton = new QPushButton(tr("Cancel"), this);
    connect(cancelButton, SIGNAL(clicked()), this, SLOT (close()));
    layout->addWidget(cancelButton,r,4,1,1);
    // Shortcuts
    QAction* findAgainAction = new QAction (this);
    findAgainAction->setShortcuts(QKeySequence::keyBindings(QKeySequence::FindNext));
    connect(findAgainAction, SIGNAL(triggered()), this, SLOT (clickFindButton()));
    addAction (findAgainAction);
    QAction* switchToFindAction = new QAction (this);
    switchToFindAction->setShortcuts(QKeySequence::keyBindings(QKeySequence::Find));
    QObject::connect(switchToFindAction, SIGNAL(triggered()), this, SLOT(switchToFind()));
    addAction (switchToFindAction);
    QAction* switchToReplaceAction = new QAction (this);
    switchToReplaceAction->setShortcuts(QKeySequence::keyBindings(QKeySequence::Replace));
    QObject::connect(switchToReplaceAction, SIGNAL(triggered()), this, SLOT(switchToReplace()));
    addAction (switchToReplaceAction);
    //
    this->setParent(mainwin);
    this->setWindowFlags(Qt::Dialog);
    Qt::WindowFlags flags = windowFlags();
    Qt::WindowFlags helpFlag = Qt::WindowContextHelpButtonHint;
    flags = flags & (~helpFlag);
    this->setWindowFlags(flags);
    this->setLayout(layout);
    this->show();
    this->layout()->setSizeConstraint( QLayout::SetFixedSize );
    changeFindText(findText->text());
    findText->setFocus();
}

void ReplaceWin::setReplaceMode(bool m) {
    replaceMode = m;
    replaceLabel->setEnabled(replaceMode);
    replaceLabel->setVisible(replaceMode);
    replaceText->setEnabled(replaceMode);
    replaceText->setVisible(replaceMode);
    replaceAllButton->setEnabled(replaceMode);
    replaceAllButton->setVisible(replaceMode);
    replaceButton->setEnabled(replaceMode);
    replaceButton->setVisible(replaceMode);
    if (replaceMode) {
        setWindowTitle(tr("BASIC-256 Find/Replace"));
    } else {
        setWindowTitle(tr("BASIC-256 Find"));
    }
    findText->setFocus();
}

void ReplaceWin::switchToFind(){
    this->setReplaceMode(false);
}

void ReplaceWin::switchToReplace(){
    this->setReplaceMode(true);
}

void ReplaceWin::changeFindText(QString t) {
    replaceButton->setEnabled(replaceMode && (t.length() != 0));
    replaceAllButton->setEnabled(replaceMode && t.length() != 0);
    findButton->setEnabled(t.length() != 0);
}

void ReplaceWin::clickFindButton() {
    findAgain();
}

void ReplaceWin::findAgain() {
    if(findText->text().length() != 0)
        editwin->findString(findText->text(), backCheckbox->isChecked(), caseCheckbox->isChecked(), wordsCheckbox->isChecked());
}

void ReplaceWin::clickReplaceButton() {
    if(findText->text().length() != 0)
        editwin->replaceString(findText->text(), replaceText->text(), backCheckbox->isChecked(), caseCheckbox->isChecked(), wordsCheckbox->isChecked(), false);
}

void ReplaceWin::clickReplaceAllButton() {
    if(findText->text().length() != 0)
        editwin->replaceString(findText->text(), replaceText->text(), backCheckbox->isChecked(), caseCheckbox->isChecked(), wordsCheckbox->isChecked(), true);
}

void ReplaceWin::closeEvent(QCloseEvent *e) {
    (void) e;
    SETTINGS;
    settings.setValue(SETTINGSREPLACEPOS, pos());
}

