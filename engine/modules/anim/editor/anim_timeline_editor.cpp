#include "anim_timeline_editor.h"
#include "engine/core/editor/editor.h"
#include "engine/core/main/Engine.h"

namespace Echo
{
#ifdef ECHO_EDITOR_MODE
	TimelineEditor::TimelineEditor(Object* object)
		: ObjectEditor(object)
		, m_timelinePanel(nullptr)
	{
		m_timelinePanel = EchoNew(TimelinePanel(object));
	}

	TimelineEditor::~TimelineEditor()
	{
		EchoSafeDelete(m_timelinePanel, TimelinePanel);
	}

	ImagePtr TimelineEditor::getThumbnail() const
	{
		return Image::loadFromFile(Engine::instance()->getRootPath() + "engine/modules/anim/editor/icon/animtimeline.png");
	}

	void TimelineEditor::onEditorSelectThisNode()
	{
		Editor::instance()->showBottomPanel(m_timelinePanel);

		m_timelinePanel->syncDataToEditor();
	}

	void TimelineEditor::editor_update_self()
	{
		if (m_timelinePanel)
		{
			m_timelinePanel->update();
		}
	}
#endif
}