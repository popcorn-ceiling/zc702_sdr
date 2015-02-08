function varargout = dsbamPanel(varargin)
% DSBAMPANEL MATLAB code for dsbamPanel.fig
%      DSBAMPANEL, by itself, creates a new DSBAMPANEL or raises the existing
%      singleton*.
%
%      H = DSBAMPANEL returns the handle to a new DSBAMPANEL or the handle to
%      the existing singleton*.
%
%      DSBAMPANEL('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in DSBAMPANEL.M with the given input arguments.
%
%      DSBAMPANEL('Property','Value',...) creates a new DSBAMPANEL or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before dsbamPanel_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to dsbamPanel_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help dsbamPanel

% Last Modified by GUIDE v2.5 07-Feb-2015 16:48:32

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @dsbamPanel_OpeningFcn, ...
                   'gui_OutputFcn',  @dsbamPanel_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before dsbamPanel is made visible.
function dsbamPanel_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to dsbamPanel (see VARARGIN)

% Choose default command line output for dsbamPanel
handles.output = hObject;

%message tone property handles
handles.messfreq = '0';
handles.messamp = '0';
handles.messphase = '0';

%carrier property handles
handles.carramp = '0';
handles.carrfreq = '0';
handles.carrphase = '0';

%system handles
handles.speriod = '0';
handles.bias = '0';

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes dsbamPanel wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = dsbamPanel_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in dsbamOKB.
function dsbamOKB_Callback(hObject, eventdata, handles)
% hObject    handle to dsbamOKB (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

set_param('RadioSYS/DSBAM/mt','Amplitude',handles.messamp);
set_param('RadioSYS/DSBAM/mt','Frequency',handles.messfreq);
set_param('RadioSYS/DSBAM/mt','Phase',handles.messphase);
set_param('RadioSYS/DSBAM/mt','Bias',handles.bias);
set_param('RadioSYS/DSBAM/mt','SampleTime',handles.speriod);
set_param('RadioSYS/DSBAM/carrier','Amplitude',handles.carramp);
set_param('RadioSYS/DSBAM/carrier','Frequency',handles.carrfreq);
set_param('RadioSYS/DSBAM/carrier','Phase',handles.carrphase);
set_param('RadioSYS/DSBAM/carrier','SampleTime',handles.speriod);


function carrierampET_Callback(hObject, eventdata, handles)
% hObject    handle to carrierampET (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of carrierampET as text
%        str2double(get(hObject,'String')) returns contents of carrierampET as a double
handles.carramp = get(hObject,'String');

guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function carrierampET_CreateFcn(hObject, eventdata, handles)
% hObject    handle to carrierampET (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function carrierfreqET_Callback(hObject, eventdata, handles)
% hObject    handle to carrierfreqET (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of carrierfreqET as text
%        str2double(get(hObject,'String')) returns contents of carrierfreqET as a double

carrfreqString = get(hObject,'String');
carrfreq = num2str(2*pi*str2double(carrfreqString));
handles.carrfreq = carrfreq;

guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function carrierfreqET_CreateFcn(hObject, eventdata, handles)
% hObject    handle to carrierfreqET (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function carrierphaseET_Callback(hObject, eventdata, handles)
% hObject    handle to carrierphaseET (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of carrierphaseET as text
%        str2double(get(hObject,'String')) returns contents of carrierphaseET as a double

carrphaseString = get(hObject,'String');
carrphase = num2str((pi*str2double(carrphaseString))/180);
handles.carrphase = carrphase;

guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function carrierphaseET_CreateFcn(hObject, eventdata, handles)
% hObject    handle to carrierphaseET (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function messageampET_Callback(hObject, eventdata, handles)
% hObject    handle to messageampET (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of messageampET as text
%        str2double(get(hObject,'String')) returns contents of messageampET as a double

handles.messamp = get(hObject,'String');

guidata(hObject, handles);



% --- Executes during object creation, after setting all properties.
function messageampET_CreateFcn(hObject, eventdata, handles)
% hObject    handle to messageampET (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function messagefreqET_Callback(hObject, eventdata, handles)
% hObject    handle to messagefreqET (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of messagefreqET as text
%        str2double(get(hObject,'String')) returns contents of messagefreqET as a double

messfreqString = get(hObject,'String');
messfreq = num2str(2*pi*str2double(messfreqString));
handles.messfreq = messfreq;

guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function messagefreqET_CreateFcn(hObject, eventdata, handles)
% hObject    handle to messagefreqET (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function messagephaseET_Callback(hObject, eventdata, handles)
% hObject    handle to messagephaseET (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of messagephaseET as text
%        str2double(get(hObject,'String')) returns contents of messagephaseET as a double

messphaseString = get(hObject,'String');
messphase = num2str((pi*str2double(messphaseString))/180);
handles.messphase = messphase;

guidata(hObject, handles);


% --- Executes during object creation, after setting all properties.
function messagephaseET_CreateFcn(hObject, eventdata, handles)
% hObject    handle to messagephaseET (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function samplerateET_Callback(hObject, eventdata, handles)
% hObject    handle to samplerateET (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of samplerateET as text
%        str2double(get(hObject,'String')) returns contents of samplerateET as a double

srateString = get(hObject,'String');
srate = str2double(srateString);
speriod = num2str(inv(srate));
handles.speriod = speriod;

guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function samplerateET_CreateFcn(hObject, eventdata, handles)
% hObject    handle to samplerateET (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function modindexET_Callback(hObject, eventdata, handles)
% hObject    handle to modindexET (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of modindexET as text
%        str2double(get(hObject,'String')) returns contents of modindexET as a double

modindexString = get(hObject,'String');
modindex = str2double(modindexString);
messamp = str2double(handles.messamp);

if messamp ~= 0 & modindex ~= 0
    bias = num2str(inv(modindex/messamp));
else
    bias = '1';
end

handles.bias = bias;
guidata(hObject, handles);



% --- Executes during object creation, after setting all properties.
function modindexET_CreateFcn(hObject, eventdata, handles)
% hObject    handle to modindexET (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in closeB.
function closeB_Callback(hObject, eventdata, handles)
% hObject    handle to closeB (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
close dsbamPanel;