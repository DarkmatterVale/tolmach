/*
 * TolmachWin.h
 *
 * This file is a part of Tolmach project - the port of KDictionary
 * for BeOS/Haiku.
 *
 * copyright: (C) 1999 by Ivan V. Murasko
 *            (C) 2003-2004 by Zyozik (BeOS-related parts)
 *            (C) 2011 by Zyozik (Renewed for Haiku)
 */
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#ifndef _TOLMACHWIN_H_
#define _TOLMACHWIN_H_


#include <list>

#include <Window.h>
#include <Menu.h>
#include <StatusBar.h>
#include <StringView.h>
#include <TextView.h>
#include <ListView.h>
#include <TextControl.h>

#include "PGBHandler.h"

class TolmachWindow : public BWindow
{
  friend class PGBHandler;
    
	class ArticleView : public BTextView {
		struct  StyleItem {
			bool  bBold;
			int32 start;
			int32 end;
	    };

		std::list<StyleItem>	aStyleItems;

	public:
				ArticleView(BRect frame, const char* name, BRect textRect,
						uint32 resizingMode, uint32 flags);
		void	ResetStyleArray(); 
		void	AppendStyleItem(bool bBold, int32 start, int32 length);
		void	ApplyStyleArray();
	virtual void FrameResized(float width, float height);
	};

    BMenuBar  *m_pMenuBar;
    BMenu     *m_pDictMenu;
    int m_nDict;
    bool m_bReverse;
    thread_id m_tid;

	bigtime_t		m_selectWordInListWatchDog;

    BStatusBar*		m_pProgress;
    BStringView*	m_pStatusView;
    
    BTextControl*	m_pWordEdit;
    BListView*		m_pWordsList;
    ArticleView*	m_pTransView;

    PGBHandler m_PGBHandler;
            
    void initMenuBar();
    void initLayout();

    void UpdateDictMenu();
    void LoadDictionary();
    static int32 LoadDictionary(void *param);
    void HandleWordEditKeyDown(BMessage *msg);
  public:
    TolmachWindow(BRect frame, int nDict, bool bReverse); 
    ~TolmachWindow(); 
    virtual bool QuitRequested();
    virtual void MessageReceived(BMessage *message);
    virtual void DispatchMessage(BMessage *msg, BHandler *target);
	virtual void FrameResized(float width, float height);

    BTextControl*	WordEdit();
    BListView*		WordsList();
    ArticleView*	TransView();
			void    SelectWordInList(int index);
			
			void    SetSelectWordInListWatchDog(bigtime_t time);
			bigtime_t   SelectWordInListWatchDog();
};


#endif //_TOLMACHWIN_H_

