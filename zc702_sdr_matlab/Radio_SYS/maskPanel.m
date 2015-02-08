function varargout = maskPanel(varargin)
% MASKPANEL MATLAB code for maskPanel.fig
%      MASKPANEL, by itself, creates a new MASKPANEL or raises the existing
%      singleton*.
%
%      H = MASKPANEL returns the handle to a new MASKPANEL or the handle to
%      the existing singleton*.
%
%      MASKPANEL('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in MASKPANEL.M with the given input arguments.
%
%      MASKPANEL('Property','Value',...) creates a new MASKPANEL or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before maskPanel_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to maskPanel_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help maskPanel

% Last Modified by GUIDE v2.5 07-Feb-2015 16:51:05

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @maskPanel_OpeningFcn, ...
                   'gui_OutputFcn',  @maskPanel_OutputFcn, ...
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


% --- Executes just before maskPanel is made visible.
function maskPanel_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to maskPanel (see VARARGIN)

% Choose default command line output for maskPanel
handles.output = hObject;


%carrier property handles
handles.carramp = '0';
handles.carrfreq = '0';
handles.carrphase = '0';

%system handles
handles.speriod = '0';
handles.binaryperiod = '0';

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes maskPanel wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = maskPanel_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in maskOKB.
function maskOKB_Callback(hObject, eventdata, handles)
% hObject    handle to maskOKB (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

set_param('RadioSYS/MASK/carrier','Amplitude',handles.carramp);
set_param('RadioSYS/MASK/carrier','Frequency',handles.carrfreq);
set_param('RadioSYS/MASK/carrier','Phase',handles.carrphase);
set_param('RadioSYS/MASK/carrier','SampleTime',handles.speriod);
set_param('RadioSYS/MASK/PRBG','Ts',handles.binaryperiod);




function amplitudeET_Callback(hObject, eventdata, handles)
% hObject    handle to amplitudeET (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of amplitudeET as text
%        str2double(get(hObject,'String')) returns contents of amplitudeET as a double

handles.carramp = get(hObject,'String');

guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function amplitudeET_CreateFcn(hObject, eventdata, handles)
% hObject    handle to amplitudeET (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function frequencyET_Callback(hObject, eventdata, handles)
% hObject    handle to frequencyET (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of frequencyET as text
%        str2double(get(hObject,'String')) returns contents of frequencyET as a double

carrfreqString = get(hObject,'String');
carrfreq = num2str(2*pi*str2double(carrfreqString));
handles.carrfreq = carrfreq;

guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function frequencyET_CreateFcn(hObject, eventdata, handles)
% hObject    handle to frequencyET (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function phaseET_Callback(hObject, eventdata, handles)
% hObject    handle to phaseET (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of phaseET as text
%        str2double(get(hObject,'String')) returns contents of phaseET as a double
carrphaseString = get(hObject,'String');
carrphase = num2str((pi*str2double(carrphaseString))/180);
handles.carrphase = carrphase;

guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function phaseET_CreateFcn(hObject, eventdata, handles)
% hObject    handle to phaseET (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function datarateET_Callback(hObject, eventdata, handles)
% hObject    handle to datarateET (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of datarateET as text
%        str2double(get(hObject,'String')) returns contents of datarateET as a double

datarateString = get(hObject,'String');
binaryperiod = num2str(inv(str2double(datarateString)));

handles.binaryperiod = binaryperiod;
guidata(hObject, handles);


% --- Executes during object creation, after setting all properties.
function datarateET_CreateFcn(hObject, eventdata, handles)
% hObject    handle to datarateET (see GCBO)
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


% --- Executes on button press in closeB.
function closeB_Callback(hObject, eventdata, handles)
% hObject    handle to closeB (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
close maskPanel;