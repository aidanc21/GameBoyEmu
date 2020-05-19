#include "debugger.h"


Debugger::Debugger(UI &ui, CPU &cpu):
m_ui(ui),
m_cpu(cpu)
{

}

Debugger::~Debugger() {

}

void Debugger::tick(uint16_t pc) {
    if (m_first_started) {
        this->help();
        m_first_started = false;

        log_debug("Starting at 0x%X", pc);
    }
    
    if (!m_stopped) {
        if (!this->check_breakpoints(pc)) {
            return;
        }
        else {
            log_debug("Stopped at 0x%X", pc);
            m_stopped = true;
        }
    }

    DebugAction_t input = this->get_input();
    m_step = false;
    
    switch (input) {
        case STEP:
            m_step = true;
            break;
        case CONTINUE:
            m_step = true;
            m_stopped = false;
            break;
        case BREAKPOINT: {
            uint16_t line_num = get_input_hex(m_arg);
            this->set_breakpoint((uint16_t)line_num);
            log_debug("Set breakpoint at 0x%X", line_num);
            break;
        }
        case PRINT:
            this->print_reg(m_arg);
            break;
        case HELP:
            this->help();
            break;
        case QUIT:
            m_quit = true;
            break;
        default:
            break;
    }
}

DebugAction_t Debugger::get_input() {
    std::vector<std::string> args = get_input_words_list();

    if (args.size() == 0) {
        return NONE;
    }
    else if (args.size() == 1) {
        std::string cmd = args[0];

        if (cmd == "s") {
            return STEP;
        }
        else if (cmd == "c") {
            return CONTINUE;
        }
        else if (cmd == "h") {
            return HELP;
        }
        else if (cmd == "q") {
            return QUIT; 
        }
    }
    else if (args.size() == 2) {
        std::string cmd = args[0];
        m_arg = args[1];
        if (cmd == "b") {
            return BREAKPOINT;
        }
        else if (cmd == "p") {
            return PRINT;
        }
    }

    return NONE;
}

void Debugger::set_breakpoint(uint16_t pc) {
    m_breakpoints.push_back(pc);
}

bool Debugger::check_breakpoints(uint16_t pc) {
    auto it = std::find(m_breakpoints.begin(), m_breakpoints.end(), pc);
    return it !=m_breakpoints.end();
}

void Debugger::print_reg(const std::string &reg) {
    log_debug("%s = 0x%X", reg.c_str(), m_cpu.read_register(reg));
}

void Debugger::help() {
    log_debug("Debugger Commands:");
    log_debug("'s': step\n'c': continue\n'b': add breakpoint\n'p': print register\n'h': help\n'q': quit");
}

bool Debugger::step() const {
    return m_step;
}

bool Debugger::quit() const {
    return m_quit;
}