#include "particle_system_panel.h"
#include "engine/core/editor/editor.h"
#include "engine/core/editor/qt/QWidgets.h"
#include "engine/core/base/class_method_bind.h"
#include "engine/core/util/PathUtil.h"
#include "engine/core/util/StringUtil.h"
#include "engine/core/io/MemoryReader.h"
#include "engine/core/util/Buffer.h"
#include "engine/core/io/IO.h"
#include "engine/core/render/base/image/Image.h"
#include "engine/core/render/base/atla/TextureAtlas.h"

namespace Echo
{
#ifdef ECHO_EDITOR_MODE
	ParticleSystemPanel::ParticleSystemPanel(Object* obj)
	{
		m_particleSystem = ECHO_DOWN_CAST<ParticleSystem*>(obj);

		m_ui = EditorApi.qLoadUi("engine/modules/effect/editor/particle_system_panel.ui");

		QWidget* splitter = EditorApi.qFindChild(m_ui, "m_splitter");
		if (splitter)
		{
			EditorApi.qSplitterSetStretchFactor(splitter, 0, 0);
			EditorApi.qSplitterSetStretchFactor(splitter, 1, 1);
		}

		// Tool button icons
		EditorApi.qToolButtonSetIcon(EditorApi.qFindChild(m_ui, "m_import"), "engine/core/render/base/editor/icon/import.png");

		// connect signal slots
		EditorApi.qConnectWidget(EditorApi.qFindChild(m_ui, "m_import"), QSIGNAL(clicked()), this, createMethodBind(&ParticleSystemPanel::onImport));
		EditorApi.qConnectWidget(EditorApi.qFindChild(m_ui, "m_nodeTreeWidget"), QSIGNAL(itemClicked(QTreeWidgetItem*, int)), this, createMethodBind(&ParticleSystemPanel::onSelectItem));
		EditorApi.qConnectWidget(EditorApi.qFindChild(m_ui, "m_nodeTreeWidget"), QSIGNAL(itemChanged(QTreeWidgetItem*, int)), this, createMethodBind(&ParticleSystemPanel::onChangedAtlaName));

		// create QGraphicsScene
		m_graphicsScene = EditorApi.qGraphicsSceneNew();
		EditorApi.qGraphicsViewSetScene(EditorApi.qFindChild(m_ui, "m_graphicsView"), m_graphicsScene);

		refreshUiDisplay();
	}

	ParticleSystemPanel::~ParticleSystemPanel()
	{
		clearImageItemAndBorder();
	}

	void ParticleSystemPanel::update()
	{
	}

	void ParticleSystemPanel::onNewAtla()
	{
	}

	void ParticleSystemPanel::onImport()
	{
		if (!m_importMenu)
		{
			m_importMenu = EditorApi.qMenuNew(m_ui);
			
			EditorApi.qMenuAddAction(m_importMenu, EditorApi.qFindChildAction(m_ui, "m_actionAddNewOne"));
			EditorApi.qMenuAddSeparator(m_importMenu);
			EditorApi.qMenuAddAction(m_importMenu, EditorApi.qFindChildAction(m_ui, "m_actionBuildFromGrid"));
			EditorApi.qMenuAddAction(m_importMenu, EditorApi.qFindChildAction(m_ui, "m_actionImportFromImages"));

			EditorApi.qConnectAction(EditorApi.qFindChildAction(m_ui, "m_actionAddNewOne"), QSIGNAL(triggered()), this, createMethodBind(&ParticleSystemPanel::onNewAtla));
			EditorApi.qConnectAction(EditorApi.qFindChildAction(m_ui, "m_actionImportFromImages"), QSIGNAL(triggered()), this, createMethodBind(&ParticleSystemPanel::onImportFromImages));
			EditorApi.qConnectAction(EditorApi.qFindChildAction(m_ui, "m_actionBuildFromGrid"), QSIGNAL(triggered()), this, createMethodBind(&ParticleSystemPanel::onSplit));
		}

		EditorApi.qMenuExec(m_importMenu);
	}

	void ParticleSystemPanel::onImportFromImages()
	{

	}

	void ParticleSystemPanel::onSplit()
	{
	}

	void ParticleSystemPanel::refreshUiDisplay()
	{
	}

	void ParticleSystemPanel::refreshAtlaList()
	{
	}

	void ParticleSystemPanel::clearImageItemAndBorder()
	{
		if (m_imageItem)
		{
			EditorApi.qGraphicsSceneDeleteItem(m_graphicsScene, m_imageItem);
			m_imageItem = nullptr;

			// because m_imageBorder is a child of m_imageItem.
			// so m_imageBorder will be delete too.
		}
	}

	void ParticleSystemPanel::refreshImageDisplay()
	{

	}

	void ParticleSystemPanel::onSelectItem()
	{

	}

	void ParticleSystemPanel::onChangedAtlaName()
	{

	}
#endif
}
