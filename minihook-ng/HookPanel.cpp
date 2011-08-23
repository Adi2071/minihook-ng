#include "HookPanel.h"

using namespace vgui;


void HookPanel::setPos(int x,int y)
{
	return m_pPanel->setPos(x, y);
}

void HookPanel::getPos(int& x,int& y)
{
	return m_pPanel->getPos(x, y);
}

void HookPanel::setSize(int wide,int tall)
{
	return m_pPanel->setSize(wide, tall);
}

void HookPanel::getSize(int& wide,int& tall)
{
	return m_pPanel->getSize(wide, tall);
}

void HookPanel::setBounds(int x,int y,int wide,int tall)
{
	return m_pPanel->setBounds(x, y, wide, tall);
}

void HookPanel::getBounds(int& x,int& y,int& wide,int& tall)
{
	return m_pPanel->getBounds(x, y, wide, tall);
}

int HookPanel::getWide()
{
	return m_pPanel->getWide();
}

int HookPanel::getTall()
{
	return m_pPanel->getTall();
}

Panel* HookPanel::getParent()
{
	return m_pPanel->getParent();
}

void HookPanel::setVisible(bool state)
{
	return m_pPanel->setVisible(state);
}

bool HookPanel::isVisible()
{
	return m_pPanel->isVisible();
}

bool HookPanel::isVisibleUp()
{
	return m_pPanel->isVisibleUp();
}

void HookPanel::repaint()
{
	return m_pPanel->repaint();
}

void HookPanel::repaintAll()
{
	return m_pPanel->repaintAll();
}

void HookPanel::getAbsExtents(int& x0,int& y0,int& x1,int& y1)
{
	return m_pPanel->getAbsExtents(x0, y0, x1, y1);
}

void HookPanel::getClipRect(int& x0,int& y0,int& x1,int& y1)
{
	return m_pPanel->getClipRect(x0, y0, x1, y1);
}

void HookPanel::setParent(Panel* newParent)
{
	return m_pPanel->setParent(newParent);
}

void HookPanel::addChild(Panel* child)
{
	return m_pPanel->addChild(child);
}

void HookPanel::insertChildAt(Panel* child,int index)
{
	return m_pPanel->insertChildAt(child, index);
}

void HookPanel::removeChild(Panel* child)
{
	return m_pPanel->removeChild(child);
}

bool HookPanel::wasMousePressed(MouseCode code)
{
	return m_pPanel->wasMousePressed(code);
}

bool HookPanel::wasMouseDoublePressed(MouseCode code)
{
	return m_pPanel->wasMouseDoublePressed(code);
}

bool HookPanel::isMouseDown(MouseCode code)
{
	return m_pPanel->isMouseDown(code);
}

bool HookPanel::wasMouseReleased(MouseCode code)
{
	return m_pPanel->wasMouseReleased(code);
}

bool HookPanel::wasKeyPressed(KeyCode code)
{
	return m_pPanel->wasKeyPressed(code);
}

bool HookPanel::isKeyDown(KeyCode code)
{
	return m_pPanel->isKeyDown(code);
}

bool HookPanel::wasKeyTyped(KeyCode code)
{
	return m_pPanel->wasKeyTyped(code);
}

bool HookPanel::wasKeyReleased(KeyCode code)
{
	return m_pPanel->wasKeyReleased(code);
}

void HookPanel::addInputSignal(InputSignal* s)
{
	return m_pPanel->addInputSignal(s);
}
void HookPanel::removeInputSignal(InputSignal* s)
{
	return m_pPanel->removeInputSignal(s);
}

void HookPanel::addRepaintSignal(RepaintSignal* s)
{
	return m_pPanel->addRepaintSignal(s);
}

void HookPanel::removeRepaintSignal(RepaintSignal* s)
{
	return m_pPanel->removeRepaintSignal(s);
}

bool HookPanel::isWithin(int x,int y)
{
	return m_pPanel->isWithin(x, y);
} //in screen space

Panel* HookPanel::isWithinTraverse(int x,int y)
{
	return m_pPanel->isWithinTraverse(x, y);
}

void HookPanel::localToScreen(int& x,int& y)
{
	return m_pPanel->localToScreen(x, y);
}

void HookPanel::screenToLocal(int& x,int& y)
{
	return m_pPanel->screenToLocal(x, y);
}

void HookPanel::setCursor(Cursor* cursor)
{
	return m_pPanel->setCursor(cursor);
}

void HookPanel::setCursor(Scheme::SchemeCursor scu)
{
	return m_pPanel->setCursor(scu);
}

Cursor* HookPanel::getCursor()
{
	return m_pPanel->getCursor();
}

void HookPanel::setMinimumSize(int wide,int tall)
{
	return m_pPanel->setMinimumSize(wide, tall);
}

void HookPanel::getMinimumSize(int& wide,int& tall)
{
	return m_pPanel->getMinimumSize(wide, tall);
}

void HookPanel::requestFocus()
{
	return m_pPanel->requestFocus();
}

bool HookPanel::hasFocus()
{
	return m_pPanel->hasFocus();
}

int  HookPanel::getChildCount()
{
	return m_pPanel->getChildCount();
}

Panel* HookPanel::getChild(int index)
{
	return m_pPanel->getChild(index);
}

void HookPanel::setLayout(Layout* layout)
{
	return m_pPanel->setLayout(layout);
}

void HookPanel::invalidateLayout(bool layoutNow)
{
	return m_pPanel->invalidateLayout(layoutNow);
}

void HookPanel::setFocusNavGroup(FocusNavGroup* focusNavGroup)
{
	return m_pPanel->setFocusNavGroup(focusNavGroup);
}

void HookPanel::requestFocusPrev()
{
	return m_pPanel->requestFocusPrev();
}

void HookPanel::requestFocusNext()
{
	return m_pPanel->requestFocusNext();
}

void HookPanel::addFocusChangeSignal(FocusChangeSignal* s)
{
	return m_pPanel->addFocusChangeSignal(s);
}

bool HookPanel::isAutoFocusNavEnabled()
{
	return m_pPanel->isAutoFocusNavEnabled();
}

void HookPanel::setAutoFocusNavEnabled(bool state)
{
	return m_pPanel->setAutoFocusNavEnabled(state);
}

void HookPanel::setBorder(Border* border)
{
	return m_pPanel->setBorder(border);
}

void HookPanel::setPaintBorderEnabled(bool state)
{
	return m_pPanel->setPaintBorderEnabled(state);
}

void HookPanel::setPaintBackgroundEnabled(bool state)
{
	return m_pPanel->setPaintBackgroundEnabled(state);
}

void HookPanel::setPaintEnabled(bool state)
{
	return m_pPanel->setPaintEnabled(state);
}

void HookPanel::getInset(int& left,int& top,int& right,int& bottom)
{
	return m_pPanel->getInset(left, top, right, bottom);
}

void HookPanel::getPaintSize(int& wide,int& tall)
{
	return m_pPanel->getPaintSize(wide, tall);
}

void HookPanel::setPreferredSize(int wide,int tall)
{
	return m_pPanel->setPreferredSize(wide, tall);
}

void HookPanel::getPreferredSize(int& wide,int& tall)
{
	return m_pPanel->getPreferredSize(wide, tall);
}

SurfaceBase* HookPanel::getSurfaceBase()
{
	return m_pPanel->getSurfaceBase();
}

bool HookPanel::isEnabled()
{
	return m_pPanel->isEnabled();
}

void HookPanel::setEnabled(bool state)
{
	return m_pPanel->setEnabled(state);
}

void HookPanel::setBuildGroup(BuildGroup* buildGroup,const char* panelPersistanceName)
{
	return m_pPanel->setBuildGroup(buildGroup, panelPersistanceName);
}

bool HookPanel::isBuildGroupEnabled()
{
	return m_pPanel->isBuildGroupEnabled();
}

void HookPanel::removeAllChildren()
{
	return m_pPanel->removeAllChildren();
}

void HookPanel::repaintParent()
{
	return m_pPanel->repaintParent();
}

Panel* HookPanel::createPropertyPanel()
{
	return m_pPanel->createPropertyPanel();
}

void HookPanel::getPersistanceText(char* buf,int bufLen)
{
	return m_pPanel->getPersistanceText(buf, bufLen);
}

void HookPanel::applyPersistanceText(const char* buf)
{
	return m_pPanel->applyPersistanceText(buf);
}

void HookPanel::setFgColor(Scheme::SchemeColor sc)
{
	return m_pPanel->setFgColor(sc);
}

void HookPanel::setBgColor(Scheme::SchemeColor sc)
{
	return m_pPanel->setBgColor(sc);
}

void HookPanel::setFgColor(int r,int g,int b,int a)
{
	return m_pPanel->setFgColor(r, g, b, a);
}

void HookPanel::setBgColor(int r,int g,int b,int a)
{
	return m_pPanel->setBgColor(r, g, b, a);
}

void HookPanel::getFgColor(int& r,int& g,int& b,int& a)
{
	return m_pPanel->getFgColor(r, g, b, a);
}

void HookPanel::getBgColor(int& r,int& g,int& b,int& a)
{
	return m_pPanel->getBgColor(r, g, b, a);
}

void HookPanel::setBgColor(Color color)
{
	return m_pPanel->setBgColor(color);
}

void HookPanel::setFgColor(Color color)
{
	return m_pPanel->setFgColor(color);
}

void HookPanel::getBgColor(Color& color)
{
	return m_pPanel->getBgColor(color);
}

void HookPanel::getFgColor(Color& color)
{
	return m_pPanel->getFgColor(color);
}

void HookPanel::setAsMouseCapture(bool state)
{
	return m_pPanel->setAsMouseCapture(state);
}

void HookPanel::setAsMouseArena(bool state)
{
	return m_pPanel->setAsMouseArena(state);
}

App* HookPanel::getApp()
{
	return m_pPanel->getApp();
}

void HookPanel::getVirtualSize(int& wide,int& tall)
{
	return m_pPanel->getVirtualSize(wide, tall);
}

void HookPanel::setLayoutInfo(LayoutInfo* layoutInfo)
{
	return m_pPanel->setLayoutInfo(layoutInfo);
}

LayoutInfo* HookPanel::getLayoutInfo()
{
	return m_pPanel->getLayoutInfo();
}

bool HookPanel::isCursorNone()
{
	return m_pPanel->isCursorNone();
}

void HookPanel::solveTraverse()
{
	return m_pPanel->solveTraverse();
}

void HookPanel::paintTraverse()
{
	return m_pPanel->paintTraverse();
}

void HookPanel::setSurfaceBaseTraverse(SurfaceBase* surfaceBase)
{
	return m_pPanel->setSurfaceBaseTraverse(surfaceBase);
}

void HookPanel::performLayout()
{
	return m_pPanel->performLayout();
}

void HookPanel::internalPerformLayout()
{
	return m_pPanel->internalPerformLayout();
}

void HookPanel::drawSetColor(Scheme::SchemeColor sc)
{
	return m_pPanel->drawSetColor(sc);
}

void HookPanel::drawSetColor(int r,int g,int b,int a)
{
	return m_pPanel->drawSetColor(r, g, b, a);
}

void HookPanel::drawFilledRect(int x0,int y0,int x1,int y1)
{
	return m_pPanel->drawFilledRect(x0, y0, x1, y1);
}

void HookPanel::drawOutlinedRect(int x0,int y0,int x1,int y1)
{
	return m_pPanel->drawOutlinedRect(x0, y0, x1, y1);
}

void HookPanel::drawSetTextFont(Scheme::SchemeFont sf)
{
	return m_pPanel->drawSetTextFont(sf);
}

void HookPanel::drawSetTextFont(Font* font)
{
	return m_pPanel->drawSetTextFont(font);
}

void HookPanel::drawSetTextColor(Scheme::SchemeColor sc)
{
	return m_pPanel->drawSetTextColor(sc);
}

void HookPanel::drawSetTextColor(int r,int g,int b,int a)
{
	return m_pPanel->drawSetTextColor(r, g, b, a);
}

void HookPanel::drawSetTextPos(int x,int y)
{
	return m_pPanel->drawSetTextPos(x, y);
}

void HookPanel::drawPrintText(const char* str,int strlen)
{
	return m_pPanel->drawPrintText(str, strlen);
}

void HookPanel::drawPrintText(int x,int y,const char* str,int strlen)
{
	return m_pPanel->drawPrintText(x, y, str, strlen);
}

void HookPanel::drawPrintChar(char ch)
{
	return m_pPanel->drawPrintChar(ch);
}

void HookPanel::drawPrintChar(int x,int y,char ch)
{
	return m_pPanel->drawPrintChar(x, y, ch);
}

void HookPanel::drawSetTextureRGBA(int id,const char* rgba,int wide,int tall)
{
	return m_pPanel->drawSetTextureRGBA(id, rgba, wide, tall);
}

void HookPanel::drawSetTexture(int id)
{
	return m_pPanel->drawSetTexture(id);
}

void HookPanel::drawTexturedRect(int x0,int y0,int x1,int y1)
{
	return m_pPanel->drawTexturedRect(x0, y0, x1, y1);
}

void HookPanel::solve()
{
	return m_pPanel->solve();
}

void HookPanel::paintTraverse(bool repaint)
{
	return m_pPanel->paintTraverse(repaint);
}

void HookPanel::paintBackground()
{
	return m_pPanel->paintBackground();
}

void HookPanel::paint()
{
	return m_pPanel->paint();
}

void HookPanel::paintBuildOverlay()
{
	return m_pPanel->paintBuildOverlay();
}

void HookPanel::internalCursorMoved(int x,int y)
{
	return m_pPanel->internalCursorMoved(x, y);
}

void HookPanel::internalCursorEntered()
{
	return m_pPanel->internalCursorEntered();
}

void HookPanel::internalCursorExited()
{
	return m_pPanel->internalCursorExited();
}

void HookPanel::internalMousePressed(MouseCode code)
{
	return m_pPanel->internalMousePressed(code);
}

void HookPanel::internalMouseDoublePressed(MouseCode code)
{
	return m_pPanel->internalMouseDoublePressed(code);
}

void HookPanel::internalMouseReleased(MouseCode code)
{
	return m_pPanel->internalMouseReleased(code);
}

void HookPanel::internalMouseWheeled(int delta)
{
	return m_pPanel->internalMouseWheeled(delta);
}

void HookPanel::internalKeyPressed(KeyCode code)
{
	return m_pPanel->internalKeyPressed(code);
}

void HookPanel::internalKeyTyped(KeyCode code)
{
	return m_pPanel->internalKeyTyped(code);
}

void HookPanel::internalKeyReleased(KeyCode code)
{
	return m_pPanel->internalKeyReleased(code);
}

void HookPanel::internalKeyFocusTicked()
{
	return m_pPanel->internalKeyFocusTicked();
}

void HookPanel::internalFocusChanged(bool lost)
{
	return m_pPanel->internalFocusChanged(lost);
}

void HookPanel::internalSetCursor()
{
	return m_pPanel->internalSetCursor();
}
