#include "plugin.hpp"


struct TestModule : Module {
	enum ParamIds {
		PITCH_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		PITCH_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		SINE_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		BLINK_LIGHT,
		NUM_LIGHTS
	};

	TestModule() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(PITCH_PARAM, 0.f, 1.f, 0.f, "");
	}

	void process(const ProcessArgs& args) override {
	}
};


struct TestModuleWidget : ModuleWidget {
	TestModuleWidget(TestModule* module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/TestModule.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(15.24, 46.063)), module, TestModule::PITCH_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(15.24, 77.478)), module, TestModule::PITCH_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(15.24, 108.713)), module, TestModule::SINE_OUTPUT));

		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(15.24, 25.81)), module, TestModule::BLINK_LIGHT));
	}
};


Model* modelTestModule = createModel<TestModule, TestModuleWidget>("TestModule");