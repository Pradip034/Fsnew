# This file was automatically generated by SWIG (http://www.swig.org).
# Version 3.0.12
#
# Do not make changes to this file unless you know what you are doing--modify
# the SWIG interface file instead.

from sys import version_info as _swig_python_version_info
if _swig_python_version_info >= (2, 7, 0):
    def swig_import_helper():
        import importlib
        pkg = __name__.rpartition('.')[0]
        mname = '.'.join((pkg, '_freeswitch')).lstrip('.')
        try:
            return importlib.import_module(mname)
        except ImportError:
            return importlib.import_module('_freeswitch')
    _freeswitch = swig_import_helper()
    del swig_import_helper
elif _swig_python_version_info >= (2, 6, 0):
    def swig_import_helper():
        from os.path import dirname
        import imp
        fp = None
        try:
            fp, pathname, description = imp.find_module('_freeswitch', [dirname(__file__)])
        except ImportError:
            import _freeswitch
            return _freeswitch
        try:
            _mod = imp.load_module('_freeswitch', fp, pathname, description)
        finally:
            if fp is not None:
                fp.close()
        return _mod
    _freeswitch = swig_import_helper()
    del swig_import_helper
else:
    import _freeswitch
del _swig_python_version_info

try:
    _swig_property = property
except NameError:
    pass  # Python < 2.2 doesn't have 'property'.

try:
    import builtins as __builtin__
except ImportError:
    import __builtin__

def _swig_setattr_nondynamic(self, class_type, name, value, static=1):
    if (name == "thisown"):
        return self.this.own(value)
    if (name == "this"):
        if type(value).__name__ == 'SwigPyObject':
            self.__dict__[name] = value
            return
    method = class_type.__swig_setmethods__.get(name, None)
    if method:
        return method(self, value)
    if (not static):
        if _newclass:
            object.__setattr__(self, name, value)
        else:
            self.__dict__[name] = value
    else:
        raise AttributeError("You cannot add attributes to %s" % self)


def _swig_setattr(self, class_type, name, value):
    return _swig_setattr_nondynamic(self, class_type, name, value, 0)


def _swig_getattr(self, class_type, name):
    if (name == "thisown"):
        return self.this.own()
    method = class_type.__swig_getmethods__.get(name, None)
    if method:
        return method(self)
    raise AttributeError("'%s' object has no attribute '%s'" % (class_type.__name__, name))


def _swig_repr(self):
    try:
        strthis = "proxy of " + self.this.__repr__()
    except __builtin__.Exception:
        strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)

try:
    _object = object
    _newclass = 1
except __builtin__.Exception:
    class _object:
        pass
    _newclass = 0


def setGlobalVariable(var_name, var_val):
    return _freeswitch.setGlobalVariable(var_name, var_val)
setGlobalVariable = _freeswitch.setGlobalVariable

def getGlobalVariable(var_name):
    return _freeswitch.getGlobalVariable(var_name)
getGlobalVariable = _freeswitch.getGlobalVariable

def consoleLog(level_str, msg):
    return _freeswitch.consoleLog(level_str, msg)
consoleLog = _freeswitch.consoleLog

def consoleLog2(level_str, file, func, line, msg):
    return _freeswitch.consoleLog2(level_str, file, func, line, msg)
consoleLog2 = _freeswitch.consoleLog2

def consoleCleanLog(msg):
    return _freeswitch.consoleCleanLog(msg)
consoleCleanLog = _freeswitch.consoleCleanLog

def running():
    return _freeswitch.running()
running = _freeswitch.running

def email(to, arg2, headers=None, body=None, file=None, convert_cmd=None, convert_ext=None):
    return _freeswitch.email(to, arg2, headers, body, file, convert_cmd, convert_ext)
email = _freeswitch.email
class IVRMenu(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, IVRMenu, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, IVRMenu, name)
    __repr__ = _swig_repr

    def __init__(self, main, name, greeting_sound, short_greeting_sound, invalid_sound, exit_sound, transfer_sound, confirm_macro, confirm_key, tts_engine, tts_voice, confirm_attempts, inter_timeout, digit_len, timeout, max_failures, max_timeouts):
        this = _freeswitch.new_IVRMenu(main, name, greeting_sound, short_greeting_sound, invalid_sound, exit_sound, transfer_sound, confirm_macro, confirm_key, tts_engine, tts_voice, confirm_attempts, inter_timeout, digit_len, timeout, max_failures, max_timeouts)
        try:
            self.this.append(this)
        except __builtin__.Exception:
            self.this = this
    __swig_destroy__ = _freeswitch.delete_IVRMenu
    __del__ = lambda self: None

    def bindAction(self, action, arg, bind):
        return _freeswitch.IVRMenu_bindAction(self, action, arg, bind)

    def execute(self, session, name):
        return _freeswitch.IVRMenu_execute(self, session, name)
IVRMenu_swigregister = _freeswitch.IVRMenu_swigregister
IVRMenu_swigregister(IVRMenu)

class API(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, API, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, API, name)
    __repr__ = _swig_repr

    def __init__(self, s=None):
        this = _freeswitch.new_API(s)
        try:
            self.this.append(this)
        except __builtin__.Exception:
            self.this = this
    __swig_destroy__ = _freeswitch.delete_API
    __del__ = lambda self: None

    def execute(self, command, data=None):
        return _freeswitch.API_execute(self, command, data)

    def executeString(self, command):
        return _freeswitch.API_executeString(self, command)

    def getTime(self):
        return _freeswitch.API_getTime(self)
API_swigregister = _freeswitch.API_swigregister
API_swigregister(API)

class input_callback_state_t(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, input_callback_state_t, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, input_callback_state_t, name)
    __repr__ = _swig_repr
    __swig_setmethods__["function"] = _freeswitch.input_callback_state_t_function_set
    __swig_getmethods__["function"] = _freeswitch.input_callback_state_t_function_get
    if _newclass:
        function = _swig_property(_freeswitch.input_callback_state_t_function_get, _freeswitch.input_callback_state_t_function_set)
    __swig_setmethods__["threadState"] = _freeswitch.input_callback_state_t_threadState_set
    __swig_getmethods__["threadState"] = _freeswitch.input_callback_state_t_threadState_get
    if _newclass:
        threadState = _swig_property(_freeswitch.input_callback_state_t_threadState_get, _freeswitch.input_callback_state_t_threadState_set)
    __swig_setmethods__["extra"] = _freeswitch.input_callback_state_t_extra_set
    __swig_getmethods__["extra"] = _freeswitch.input_callback_state_t_extra_get
    if _newclass:
        extra = _swig_property(_freeswitch.input_callback_state_t_extra_get, _freeswitch.input_callback_state_t_extra_set)
    __swig_setmethods__["funcargs"] = _freeswitch.input_callback_state_t_funcargs_set
    __swig_getmethods__["funcargs"] = _freeswitch.input_callback_state_t_funcargs_get
    if _newclass:
        funcargs = _swig_property(_freeswitch.input_callback_state_t_funcargs_get, _freeswitch.input_callback_state_t_funcargs_set)

    def __init__(self):
        this = _freeswitch.new_input_callback_state_t()
        try:
            self.this.append(this)
        except __builtin__.Exception:
            self.this = this
    __swig_destroy__ = _freeswitch.delete_input_callback_state_t
    __del__ = lambda self: None
input_callback_state_t_swigregister = _freeswitch.input_callback_state_t_swigregister
input_callback_state_t_swigregister(input_callback_state_t)

S_HUP = _freeswitch.S_HUP
S_FREE = _freeswitch.S_FREE
S_RDLOCK = _freeswitch.S_RDLOCK
class DTMF(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, DTMF, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, DTMF, name)
    __repr__ = _swig_repr
    __swig_setmethods__["digit"] = _freeswitch.DTMF_digit_set
    __swig_getmethods__["digit"] = _freeswitch.DTMF_digit_get
    if _newclass:
        digit = _swig_property(_freeswitch.DTMF_digit_get, _freeswitch.DTMF_digit_set)
    __swig_setmethods__["duration"] = _freeswitch.DTMF_duration_set
    __swig_getmethods__["duration"] = _freeswitch.DTMF_duration_get
    if _newclass:
        duration = _swig_property(_freeswitch.DTMF_duration_get, _freeswitch.DTMF_duration_set)

    def __init__(self, *args):
        this = _freeswitch.new_DTMF(*args)
        try:
            self.this.append(this)
        except __builtin__.Exception:
            self.this = this
    __swig_destroy__ = _freeswitch.delete_DTMF
    __del__ = lambda self: None
DTMF_swigregister = _freeswitch.DTMF_swigregister
DTMF_swigregister(DTMF)

class Stream(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Stream, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Stream, name)
    __repr__ = _swig_repr

    def __init__(self, *args):
        this = _freeswitch.new_Stream(*args)
        try:
            self.this.append(this)
        except __builtin__.Exception:
            self.this = this
    __swig_destroy__ = _freeswitch.delete_Stream
    __del__ = lambda self: None

    def read(self, len):
        return _freeswitch.Stream_read(self, len)

    def write(self, data):
        return _freeswitch.Stream_write(self, data)

    def raw_write(self, data, len):
        return _freeswitch.Stream_raw_write(self, data, len)

    def get_data(self):
        return _freeswitch.Stream_get_data(self)
Stream_swigregister = _freeswitch.Stream_swigregister
Stream_swigregister(Stream)

class Event(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Event, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Event, name)
    __repr__ = _swig_repr
    __swig_setmethods__["event"] = _freeswitch.Event_event_set
    __swig_getmethods__["event"] = _freeswitch.Event_event_get
    if _newclass:
        event = _swig_property(_freeswitch.Event_event_get, _freeswitch.Event_event_set)
    __swig_setmethods__["serialized_string"] = _freeswitch.Event_serialized_string_set
    __swig_getmethods__["serialized_string"] = _freeswitch.Event_serialized_string_get
    if _newclass:
        serialized_string = _swig_property(_freeswitch.Event_serialized_string_get, _freeswitch.Event_serialized_string_set)
    __swig_setmethods__["mine"] = _freeswitch.Event_mine_set
    __swig_getmethods__["mine"] = _freeswitch.Event_mine_get
    if _newclass:
        mine = _swig_property(_freeswitch.Event_mine_get, _freeswitch.Event_mine_set)

    def __init__(self, *args):
        this = _freeswitch.new_Event(*args)
        try:
            self.this.append(this)
        except __builtin__.Exception:
            self.this = this
    __swig_destroy__ = _freeswitch.delete_Event
    __del__ = lambda self: None

    def chat_execute(self, app, data=None):
        return _freeswitch.Event_chat_execute(self, app, data)

    def chat_send(self, dest_proto=None):
        return _freeswitch.Event_chat_send(self, dest_proto)

    def serialize(self, format=None):
        return _freeswitch.Event_serialize(self, format)

    def setPriority(self, *args):
        return _freeswitch.Event_setPriority(self, *args)

    def getHeader(self, header_name):
        return _freeswitch.Event_getHeader(self, header_name)

    def getBody(self):
        return _freeswitch.Event_getBody(self)

    def getType(self):
        return _freeswitch.Event_getType(self)

    def addBody(self, value):
        return _freeswitch.Event_addBody(self, value)

    def addHeader(self, header_name, value):
        return _freeswitch.Event_addHeader(self, header_name, value)

    def delHeader(self, header_name):
        return _freeswitch.Event_delHeader(self, header_name)

    def fire(self):
        return _freeswitch.Event_fire(self)

    def merge(self, to_merge):
        return _freeswitch.Event_merge(self, to_merge)
Event_swigregister = _freeswitch.Event_swigregister
Event_swigregister(Event)

class EventConsumer(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, EventConsumer, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, EventConsumer, name)
    __repr__ = _swig_repr
    __swig_setmethods__["events"] = _freeswitch.EventConsumer_events_set
    __swig_getmethods__["events"] = _freeswitch.EventConsumer_events_get
    if _newclass:
        events = _swig_property(_freeswitch.EventConsumer_events_get, _freeswitch.EventConsumer_events_set)
    __swig_setmethods__["e_event_id"] = _freeswitch.EventConsumer_e_event_id_set
    __swig_getmethods__["e_event_id"] = _freeswitch.EventConsumer_e_event_id_get
    if _newclass:
        e_event_id = _swig_property(_freeswitch.EventConsumer_e_event_id_get, _freeswitch.EventConsumer_e_event_id_set)
    __swig_setmethods__["e_callback"] = _freeswitch.EventConsumer_e_callback_set
    __swig_getmethods__["e_callback"] = _freeswitch.EventConsumer_e_callback_get
    if _newclass:
        e_callback = _swig_property(_freeswitch.EventConsumer_e_callback_get, _freeswitch.EventConsumer_e_callback_set)
    __swig_setmethods__["e_subclass_name"] = _freeswitch.EventConsumer_e_subclass_name_set
    __swig_getmethods__["e_subclass_name"] = _freeswitch.EventConsumer_e_subclass_name_get
    if _newclass:
        e_subclass_name = _swig_property(_freeswitch.EventConsumer_e_subclass_name_get, _freeswitch.EventConsumer_e_subclass_name_set)
    __swig_setmethods__["e_cb_arg"] = _freeswitch.EventConsumer_e_cb_arg_set
    __swig_getmethods__["e_cb_arg"] = _freeswitch.EventConsumer_e_cb_arg_get
    if _newclass:
        e_cb_arg = _swig_property(_freeswitch.EventConsumer_e_cb_arg_get, _freeswitch.EventConsumer_e_cb_arg_set)
    __swig_setmethods__["enodes"] = _freeswitch.EventConsumer_enodes_set
    __swig_getmethods__["enodes"] = _freeswitch.EventConsumer_enodes_get
    if _newclass:
        enodes = _swig_property(_freeswitch.EventConsumer_enodes_get, _freeswitch.EventConsumer_enodes_set)
    __swig_setmethods__["node_index"] = _freeswitch.EventConsumer_node_index_set
    __swig_getmethods__["node_index"] = _freeswitch.EventConsumer_node_index_get
    if _newclass:
        node_index = _swig_property(_freeswitch.EventConsumer_node_index_get, _freeswitch.EventConsumer_node_index_set)

    def __init__(self, *args):
        this = _freeswitch.new_EventConsumer(*args)
        try:
            self.this.append(this)
        except __builtin__.Exception:
            self.this = this
    __swig_destroy__ = _freeswitch.delete_EventConsumer
    __del__ = lambda self: None

    def bind(self, *args):
        return _freeswitch.EventConsumer_bind(self, *args)

    def pop(self, block=0, timeout=0):
        return _freeswitch.EventConsumer_pop(self, block, timeout)

    def cleanup(self):
        return _freeswitch.EventConsumer_cleanup(self)
EventConsumer_swigregister = _freeswitch.EventConsumer_swigregister
EventConsumer_swigregister(EventConsumer)

class CoreSession(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, CoreSession, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, CoreSession, name)

    def __init__(self, *args, **kwargs):
        raise AttributeError("No constructor defined - class is abstract")
    __repr__ = _swig_repr
    __swig_destroy__ = _freeswitch.delete_CoreSession
    __del__ = lambda self: None
    __swig_setmethods__["session"] = _freeswitch.CoreSession_session_set
    __swig_getmethods__["session"] = _freeswitch.CoreSession_session_get
    if _newclass:
        session = _swig_property(_freeswitch.CoreSession_session_get, _freeswitch.CoreSession_session_set)
    __swig_setmethods__["channel"] = _freeswitch.CoreSession_channel_set
    __swig_getmethods__["channel"] = _freeswitch.CoreSession_channel_get
    if _newclass:
        channel = _swig_property(_freeswitch.CoreSession_channel_get, _freeswitch.CoreSession_channel_set)
    __swig_setmethods__["flags"] = _freeswitch.CoreSession_flags_set
    __swig_getmethods__["flags"] = _freeswitch.CoreSession_flags_get
    if _newclass:
        flags = _swig_property(_freeswitch.CoreSession_flags_get, _freeswitch.CoreSession_flags_set)
    __swig_setmethods__["allocated"] = _freeswitch.CoreSession_allocated_set
    __swig_getmethods__["allocated"] = _freeswitch.CoreSession_allocated_get
    if _newclass:
        allocated = _swig_property(_freeswitch.CoreSession_allocated_get, _freeswitch.CoreSession_allocated_set)
    __swig_setmethods__["cb_state"] = _freeswitch.CoreSession_cb_state_set
    __swig_getmethods__["cb_state"] = _freeswitch.CoreSession_cb_state_get
    if _newclass:
        cb_state = _swig_property(_freeswitch.CoreSession_cb_state_get, _freeswitch.CoreSession_cb_state_set)
    __swig_setmethods__["hook_state"] = _freeswitch.CoreSession_hook_state_set
    __swig_getmethods__["hook_state"] = _freeswitch.CoreSession_hook_state_get
    if _newclass:
        hook_state = _swig_property(_freeswitch.CoreSession_hook_state_get, _freeswitch.CoreSession_hook_state_set)
    __swig_setmethods__["cause"] = _freeswitch.CoreSession_cause_set
    __swig_getmethods__["cause"] = _freeswitch.CoreSession_cause_get
    if _newclass:
        cause = _swig_property(_freeswitch.CoreSession_cause_get, _freeswitch.CoreSession_cause_set)
    __swig_setmethods__["uuid"] = _freeswitch.CoreSession_uuid_set
    __swig_getmethods__["uuid"] = _freeswitch.CoreSession_uuid_get
    if _newclass:
        uuid = _swig_property(_freeswitch.CoreSession_uuid_get, _freeswitch.CoreSession_uuid_set)
    __swig_setmethods__["tts_name"] = _freeswitch.CoreSession_tts_name_set
    __swig_getmethods__["tts_name"] = _freeswitch.CoreSession_tts_name_get
    if _newclass:
        tts_name = _swig_property(_freeswitch.CoreSession_tts_name_get, _freeswitch.CoreSession_tts_name_set)
    __swig_setmethods__["voice_name"] = _freeswitch.CoreSession_voice_name_set
    __swig_getmethods__["voice_name"] = _freeswitch.CoreSession_voice_name_get
    if _newclass:
        voice_name = _swig_property(_freeswitch.CoreSession_voice_name_get, _freeswitch.CoreSession_voice_name_set)

    def insertFile(self, file, insert_file, sample_point):
        return _freeswitch.CoreSession_insertFile(self, file, insert_file, sample_point)

    def answer(self):
        return _freeswitch.CoreSession_answer(self)

    def _print(self, txt):
        return _freeswitch.CoreSession__print(self, txt)

    def preAnswer(self):
        return _freeswitch.CoreSession_preAnswer(self)

    def hangup(self, *args):
        return _freeswitch.CoreSession_hangup(self, *args)

    def hangupState(self):
        return _freeswitch.CoreSession_hangupState(self)

    def setVariable(self, var, val):
        return _freeswitch.CoreSession_setVariable(self, var, val)

    def setPrivate(self, var, val):
        return _freeswitch.CoreSession_setPrivate(self, var, val)

    def getPrivate(self, var):
        return _freeswitch.CoreSession_getPrivate(self, var)

    def getVariable(self, var):
        return _freeswitch.CoreSession_getVariable(self, var)

    def process_callback_result(self, result):
        return _freeswitch.CoreSession_process_callback_result(self, result)

    def say(self, tosay, module_name, say_type, say_method, say_gender=None):
        return _freeswitch.CoreSession_say(self, tosay, module_name, say_type, say_method, say_gender)

    def sayPhrase(self, *args):
        return _freeswitch.CoreSession_sayPhrase(self, *args)

    def hangupCause(self):
        return _freeswitch.CoreSession_hangupCause(self)

    def getState(self):
        return _freeswitch.CoreSession_getState(self)

    def recordFile(self, file_name, time_limit=0, silence_threshold=0, silence_hits=0):
        return _freeswitch.CoreSession_recordFile(self, file_name, time_limit, silence_threshold, silence_hits)

    def originate(self, a_leg_session, dest, timeout=60, handlers=None):
        return _freeswitch.CoreSession_originate(self, a_leg_session, dest, timeout, handlers)

    def destroy(self):
        return _freeswitch.CoreSession_destroy(self)

    def setDTMFCallback(self, cbfunc, funcargs):
        return _freeswitch.CoreSession_setDTMFCallback(self, cbfunc, funcargs)

    def speak(self, text):
        return _freeswitch.CoreSession_speak(self, text)

    def set_tts_parms(self, tts_name, voice_name):
        return _freeswitch.CoreSession_set_tts_parms(self, tts_name, voice_name)

    def set_tts_params(self, tts_name, voice_name):
        return _freeswitch.CoreSession_set_tts_params(self, tts_name, voice_name)

    def collectDigits(self, *args):
        return _freeswitch.CoreSession_collectDigits(self, *args)

    def getDigits(self, *args):
        return _freeswitch.CoreSession_getDigits(self, *args)

    def transfer(self, extension, dialplan=None, context=None):
        return _freeswitch.CoreSession_transfer(self, extension, dialplan, context)

    def read(self, min_digits, max_digits, prompt_audio_file, timeout, valid_terminators, digit_timeout=0):
        return _freeswitch.CoreSession_read(self, min_digits, max_digits, prompt_audio_file, timeout, valid_terminators, digit_timeout)

    def detectSpeech(self, arg0, arg1=None, arg2=None, arg3=None):
        return _freeswitch.CoreSession_detectSpeech(self, arg0, arg1, arg2, arg3)

    def playAndGetDigits(self, min_digits, max_digits, max_tries, timeout, terminators, audio_files, bad_input_audio_files, digits_regex, var_name=None, digit_timeout=0, transfer_on_failure=None):
        return _freeswitch.CoreSession_playAndGetDigits(self, min_digits, max_digits, max_tries, timeout, terminators, audio_files, bad_input_audio_files, digits_regex, var_name, digit_timeout, transfer_on_failure)

    def playAndDetectSpeech(self, file, engine, grammar):
        return _freeswitch.CoreSession_playAndDetectSpeech(self, file, engine, grammar)

    def streamFile(self, file, starting_sample_count=0):
        return _freeswitch.CoreSession_streamFile(self, file, starting_sample_count)

    def sleep(self, ms, sync=0):
        return _freeswitch.CoreSession_sleep(self, ms, sync)

    def flushEvents(self):
        return _freeswitch.CoreSession_flushEvents(self)

    def flushDigits(self):
        return _freeswitch.CoreSession_flushDigits(self)

    def setAutoHangup(self, val):
        return _freeswitch.CoreSession_setAutoHangup(self, val)

    def setHangupHook(self, hangup_func):
        return _freeswitch.CoreSession_setHangupHook(self, hangup_func)

    def ready(self):
        return _freeswitch.CoreSession_ready(self)

    def bridged(self):
        return _freeswitch.CoreSession_bridged(self)

    def answered(self):
        return _freeswitch.CoreSession_answered(self)

    def mediaReady(self):
        return _freeswitch.CoreSession_mediaReady(self)

    def waitForAnswer(self, calling_session):
        return _freeswitch.CoreSession_waitForAnswer(self, calling_session)

    def execute(self, app, data=None):
        return _freeswitch.CoreSession_execute(self, app, data)

    def sendEvent(self, sendME):
        return _freeswitch.CoreSession_sendEvent(self, sendME)

    def setEventData(self, e):
        return _freeswitch.CoreSession_setEventData(self, e)

    def getXMLCDR(self):
        return _freeswitch.CoreSession_getXMLCDR(self)

    def begin_allow_threads(self):
        return _freeswitch.CoreSession_begin_allow_threads(self)

    def end_allow_threads(self):
        return _freeswitch.CoreSession_end_allow_threads(self)

    def get_uuid(self):
        return _freeswitch.CoreSession_get_uuid(self)

    def get_cb_args(self):
        return _freeswitch.CoreSession_get_cb_args(self)

    def check_hangup_hook(self):
        return _freeswitch.CoreSession_check_hangup_hook(self)

    def run_dtmf_callback(self, input, itype):
        return _freeswitch.CoreSession_run_dtmf_callback(self, input, itype)

    def consoleLog(self, level_str, msg):
        return _freeswitch.CoreSession_consoleLog(self, level_str, msg)

    def consoleLog2(self, level_str, file, func, line, msg):
        return _freeswitch.CoreSession_consoleLog2(self, level_str, file, func, line, msg)
CoreSession_swigregister = _freeswitch.CoreSession_swigregister
CoreSession_swigregister(CoreSession)


def console_log(level_str, msg):
    return _freeswitch.console_log(level_str, msg)
console_log = _freeswitch.console_log

def console_log2(level_str, file, func, line, msg):
    return _freeswitch.console_log2(level_str, file, func, line, msg)
console_log2 = _freeswitch.console_log2

def console_clean_log(msg):
    return _freeswitch.console_clean_log(msg)
console_clean_log = _freeswitch.console_clean_log

def msleep(ms):
    return _freeswitch.msleep(ms)
msleep = _freeswitch.msleep

def bridge(session_a, session_b):
    return _freeswitch.bridge(session_a, session_b)
bridge = _freeswitch.bridge

def hanguphook(session):
    return _freeswitch.hanguphook(session)
hanguphook = _freeswitch.hanguphook

def dtmf_callback(session, input, itype, buf, buflen):
    return _freeswitch.dtmf_callback(session, input, itype, buf, buflen)
dtmf_callback = _freeswitch.dtmf_callback
class Session(CoreSession):
    __swig_setmethods__ = {}
    for _s in [CoreSession]:
        __swig_setmethods__.update(getattr(_s, '__swig_setmethods__', {}))
    __setattr__ = lambda self, name, value: _swig_setattr(self, Session, name, value)
    __swig_getmethods__ = {}
    for _s in [CoreSession]:
        __swig_getmethods__.update(getattr(_s, '__swig_getmethods__', {}))
    __getattr__ = lambda self, name: _swig_getattr(self, Session, name)
    __repr__ = _swig_repr

    def __init__(self, *args):
        this = _freeswitch.new_Session(*args)
        try:
            self.this.append(this)
        except __builtin__.Exception:
            self.this = this
    __swig_destroy__ = _freeswitch.delete_Session
    __del__ = lambda self: None

    def begin_allow_threads(self):
        return _freeswitch.Session_begin_allow_threads(self)

    def end_allow_threads(self):
        return _freeswitch.Session_end_allow_threads(self)

    def check_hangup_hook(self):
        return _freeswitch.Session_check_hangup_hook(self)

    def destroy(self):
        return _freeswitch.Session_destroy(self)

    def run_dtmf_callback(self, input, itype):
        return _freeswitch.Session_run_dtmf_callback(self, input, itype)

    def setInputCallback(self, cbfunc, funcargs=None):
        return _freeswitch.Session_setInputCallback(self, cbfunc, funcargs)

    def unsetInputCallback(self):
        return _freeswitch.Session_unsetInputCallback(self)

    def setHangupHook(self, pyfunc, arg=None):
        return _freeswitch.Session_setHangupHook(self, pyfunc, arg)

    def ready(self):
        return _freeswitch.Session_ready(self)
    __swig_setmethods__["cb_function"] = _freeswitch.Session_cb_function_set
    __swig_getmethods__["cb_function"] = _freeswitch.Session_cb_function_get
    if _newclass:
        cb_function = _swig_property(_freeswitch.Session_cb_function_get, _freeswitch.Session_cb_function_set)
    __swig_setmethods__["cb_arg"] = _freeswitch.Session_cb_arg_set
    __swig_getmethods__["cb_arg"] = _freeswitch.Session_cb_arg_get
    if _newclass:
        cb_arg = _swig_property(_freeswitch.Session_cb_arg_get, _freeswitch.Session_cb_arg_set)
    __swig_setmethods__["hangup_func"] = _freeswitch.Session_hangup_func_set
    __swig_getmethods__["hangup_func"] = _freeswitch.Session_hangup_func_get
    if _newclass:
        hangup_func = _swig_property(_freeswitch.Session_hangup_func_get, _freeswitch.Session_hangup_func_set)
    __swig_setmethods__["hangup_func_arg"] = _freeswitch.Session_hangup_func_arg_set
    __swig_getmethods__["hangup_func_arg"] = _freeswitch.Session_hangup_func_arg_get
    if _newclass:
        hangup_func_arg = _swig_property(_freeswitch.Session_hangup_func_arg_get, _freeswitch.Session_hangup_func_arg_set)

    def setPython(self, state):
        return _freeswitch.Session_setPython(self, state)

    def setSelf(self, state):
        return _freeswitch.Session_setSelf(self, state)
Session_swigregister = _freeswitch.Session_swigregister
Session_swigregister(Session)

# This file is compatible with both classic and new-style classes.


