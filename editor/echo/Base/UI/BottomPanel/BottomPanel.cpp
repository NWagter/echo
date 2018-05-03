#include "BottomPanel.h"
#include <QListWidgetItem>
#include "TimelinePanel.h"
#include "DebuggerPanel.h"
#include "LogPanel.h"
#include "Studio.h"

namespace Studio
{
	// 构造函数
	BottomPanel::BottomPanel(QWidget* parent/* = 0*/)
		: QDockWidget( parent)
	{
		setupUi(this);

		m_timelinePanel = EchoNew(TimelinePanel(this));
		m_debuggerPanel = EchoNew(DebuggerPanel(this));

		m_tabWidget->clear();
		m_tabWidget->addTab(AStudio::Instance()->getLogPanel(), "Log");
		m_tabWidget->addTab(m_debuggerPanel, "Debugger");
		m_tabWidget->addTab(m_timelinePanel, "TimeLine");
	}

	// 析构函数
	BottomPanel::~BottomPanel()
	{
	}
}