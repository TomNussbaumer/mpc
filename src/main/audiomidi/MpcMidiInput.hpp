#pragma once

#include <observer/Observable.hpp>
#include <sequencer/Event.hpp>
#include <sequencer/Track.hpp>
#include <midi/core/MidiInput.hpp>
#include <sequencer/EventAdapter.hpp>
#include <sequencer/MidiAdapter.hpp>

#include <memory>

namespace mpc::ui::sequencer::window {
	class SequencerWindowGui;
}
		
namespace mpc::ui::midisync {
	class MidiSyncGui;
}

namespace mpc::audiomidi {
	class MpcMidiPorts;
}
namespace mpc::audiomidi {
	class MpcMidiInput
		: public moduru::observer::Observable
		, public virtual ctoot::midi::core::MidiInput
	{

	public:
		int index = 0;

	private:
		std::weak_ptr<mpc::sequencer::Sequencer> sequencer;
		std::weak_ptr<mpc::sampler::Sampler> sampler;
		mpc::ui::midisync::MidiSyncGui* msGui = nullptr;
		mpc::ui::sequencer::window::SequencerWindowGui* swGui = nullptr;
		mpc::Mpc* mpc{ nullptr };
		std::unique_ptr<mpc::sequencer::MidiAdapter> midiAdapter;
		std::unique_ptr<mpc::sequencer::EventAdapter> eventAdapter;
		std::string notify = "";

	public:
		std::string getName() override;
		void transport(ctoot::midi::core::MidiMessage* msg, int timestamp) override;

	private:
		void midiOut(std::weak_ptr<sequencer::Event> event, sequencer::Track* track);
		void transportOmni(ctoot::midi::core::MidiMessage* msg, std::string outputLetter);

	public:
		MpcMidiInput(int index, Mpc* mpc);
		~MpcMidiInput();

	};
}
