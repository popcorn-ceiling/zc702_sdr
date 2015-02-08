function varargout = radio1Panel(varargin)
% RADIO1PANEL MATLAB code for radio1Panel.fig
%      RADIO1PANEL, by itself, creates a new RADIO1PANEL or raises the existing
%      singleton*.
%
%      H = RADIO1PANEL returns the handle to a new RADIO1PANEL or the handle to
%      the existing singleton*.
%
%      RADIO1PANEL('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in RADIO1PANEL.M with the given input arguments.
%
%      RADIO1PANEL('Property','Value',...) creates a new RADIO1PANEL or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before radio1Panel_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to radio1Panel_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help radio1Panel

% Last Modified by GUIDE v2.5 07-Feb-2015 17:10:42

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @radio1Panel_OpeningFcn, ...
                   'gui_OutputFcn',  @radio1Panel_OutputFcn, ...
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


% --- Executes just before radio1Panel is made visible.
function radio1Panel_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to radio1Panel (see VARARGIN)

% Choose default command line output for radio1Panel
handles.output = hObject;

%center frequency handles
handles.iqfreq1 = '0';
handles.iqfreq2 = '0';
handles.iqfreq3 = '0';
handles.iqfreq4 = '0';


%signal parameter panel string handles
handles.sig1param = '0'
handles.sig2param = '0'
handles.sig3param = '0'
handles.sig4param = '0'


% Update handles structure
guidata(hObject, handles);

% UIWAIT makes radio1Panel wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = radio1Panel_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in rfonB.
function rfonB_Callback(hObject, eventdata, handles)
% hObject    handle to rfonB (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set_param('RadioSYS','SimulationCommand','start')

% --- Executes on button press in rfoffB.
function rfoffB_Callback(hObject, eventdata, handles)
% hObject    handle to rfoffB (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set_param('RadioSYS','SimulationCommand','stop')


function sig1centerfreqET_Callback(hObject, eventdata, handles)
% hObject    handle to sig1centerfreqET (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of sig1centerfreqET as text
%        str2double(get(hObject,'String')) returns contents of sig1centerfreqET as a double

iqfreq1String = get(hObject,'Value');
iqfreq1 = num2str(2*pi*str2double(iqfreq1String));
handles.iqfreq1 = iqfreq1;

guidata(hObject, handles);


% --- Executes during object creation, after setting all properties.
function sig1centerfreqET_CreateFcn(hObject, eventdata, handles)
% hObject    handle to sig1centerfreqET (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function sig2centerfreqET_Callback(hObject, eventdata, handles)
% hObject    handle to sig2centerfreqET (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of sig2centerfreqET as text
%        str2double(get(hObject,'String')) returns contents of sig2centerfreqET as a double

iqfreq2String = get(hObject,'Value');
iqfreq2 = num2str(2*pi*str2double(iqfreq2String));
handles.iqfreq2 = iqfreq2;

guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function sig2centerfreqET_CreateFcn(hObject, eventdata, handles)
% hObject    handle to sig2centerfreqET (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function sig3centerfreqET_Callback(hObject, eventdata, handles)
% hObject    handle to sig3centerfreqET (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of sig3centerfreqET as text
%        str2double(get(hObject,'String')) returns contents of sig3centerfreqET as a double

iqfreq3String = get(hObject,'Value');
iqfreq3 = num2str(2*pi*str2double(iqfreq3String));
handles.iqfreq3 = iqfreq3;

guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function sig3centerfreqET_CreateFcn(hObject, eventdata, handles)
% hObject    handle to sig3centerfreqET (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function sig4centerfreqET_Callback(hObject, eventdata, handles)
% hObject    handle to sig4centerfreqET (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of sig4centerfreqET as text
%        str2double(get(hObject,'String')) returns contents of sig4centerfreqET as a double

iqfreq4String = get(hObject,'Value');
iqfreq4 = num2str(2*pi*str2double(iqfreq4String));
handles.iqfreq4 = iqfreq4;

guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function sig4centerfreqET_CreateFcn(hObject, eventdata, handles)
% hObject    handle to sig4centerfreqET (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in sig1PM.
function sig1PM_Callback(hObject, eventdata, handles)
% hObject    handle to sig1PM (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns sig1PM contents as cell array
%        contents{get(hObject,'Value')} returns selected item from sig1PM
str = get(hObject, 'String');
index = get(hObject, 'Value');

switch str{index};
    case 'MASK'
        handles.sig1param = 'maskPanel.m';
        set_param('RadioSYS/From0','GotoTag','A');
        set_param('RadioSYS/From1','GotoTag','A');
    case 'DSB-LC AM'
        handles.sig1param = 'dsbamPanel.m';
        set_param('RadioSYS/From0','GotoTag','B');
        set_param('RadioSYS/From1','GotoTag','B');
        
    case 'PM'
        handles.sig1param = 'pmPanel.m';
        set_param('RadioSYS/From0','GotoTag','C');
        set_param('RadioSYS/From1','GotoTag','C');
      
    case 'FM'
        handles.sig1param = 'fmPanel.m';
        set_param('RadioSYS/From0','GotoTag','D');
        set_param('RadioSYS/From1','GotoTag','D');
        
    case 'NONE'
        handles.sig1param = '0';
        set_param('RadioSYS/From0','GotoTag','E');
        set_param('RadioSYS/From1','GotoTag','E');
end
guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function sig1PM_CreateFcn(hObject, eventdata, handles)
% hObject    handle to sig1PM (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in sig2PM.
function sig2PM_Callback(hObject, eventdata, handles)
% hObject    handle to sig2PM (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns sig2PM contents as cell array
%        contents{get(hObject,'Value')} returns selected item from sig2PM
str = get(hObject, 'String');
index = get(hObject, 'Value');

switch str{index};
    case 'MASK'
        handles.sig2param = 'maskPanel.m';
        set_param('RadioSYS/From2','GotoTag','A');
        set_param('RadioSYS/From3','GotoTag','A');
       
    case 'DSB-LC AM'
        handles.sig2param = 'dsbamPanel.m';
        set_param('RadioSYS/From2','GotoTag','B');
        set_param('RadioSYS/From3','GotoTag','B');
        
    case 'PM'
        handles.sig2param = 'pmPanel.m';
        set_param('RadioSYS/From2','GotoTag','C');
        set_param('RadioSYS/From3','GotoTag','C');
      
    case 'FM'
        handles.sig2param = 'fmPanel.m';
        set_param('RadioSYS/From2','GotoTag','D');
        set_param('RadioSYS/From3','GotoTag','D');
        
    case 'NONE'
        handles.sig2param = '0';
        set_param('RadioSYS/From2','GotoTag','E');
        set_param('RadioSYS/From3','GotoTag','E');
end
guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function sig2PM_CreateFcn(hObject, eventdata, handles)
% hObject    handle to sig2PM (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in sig3PM.
function sig3PM_Callback(hObject, eventdata, handles)
% hObject    handle to sig3PM (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns sig3PM contents as cell array
%        contents{get(hObject,'Value')} returns selected item from sig3PM
str = get(hObject, 'String');
index = get(hObject, 'Value');

switch str{index};
    case 'MASK'
        handles.sig3param = 'maskPanel.m';
        set_param('RadioSYS/From4','GotoTag','A');
        set_param('RadioSYS/From5','GotoTag','A');
       
    case 'DSB-LC AM'
        handles.sig3param = 'dsbamPanel.m';
        set_param('RadioSYS/From4','GotoTag','B');
        set_param('RadioSYS/From5','GotoTag','B');
        
    case 'PM'
        handles.sig3param = 'pmPanel.m';
        set_param('RadioSYS/From4','GotoTag','C');
        set_param('RadioSYS/From5','GotoTag','C');
      
    case 'FM'
        handles.sig3param = 'fmPanel.m';
        set_param('RadioSYS/From4','GotoTag','D');
        set_param('RadioSYS/From5','GotoTag','D');
        
    case 'NONE'
        handles.sig3param = '0';
        set_param('RadioSYS/From4','GotoTag','E');
        set_param('RadioSYS/From5','GotoTag','E');
end
guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function sig3PM_CreateFcn(hObject, eventdata, handles)
% hObject    handle to sig3PM (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in sig4PM.
function sig4PM_Callback(hObject, eventdata, handles)
% hObject    handle to sig4PM (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns sig4PM contents as cell array
%        contents{get(hObject,'Value')} returns selected item from sig4PM
str = get(hObject, 'String');
index = get(hObject, 'Value');

switch str{index};
    case 'MASK'
        handles.sig4param = 'maskPanel.m';
        set_param('RadioSYS/From6','GotoTag','A');
        set_param('RadioSYS/From7','GotoTag','A');
       
    case 'DSB-LC AM'
        handles.sig4param = 'dsbamPanel.m';
        set_param('RadioSYS/From6','GotoTag','B');
        set_param('RadioSYS/From7','GotoTag','B');
        
    case 'PM'
        handles.sig4param = 'pmPanel.m';
        set_param('RadioSYS/From6','GotoTag','C');
        set_param('RadioSYS/From7','GotoTag','C');
      
    case 'FM'
        handles.sig4param = 'fmPanel.m';
        set_param('RadioSYS/From6','GotoTag','D');
        set_param('RadioSYS/From7','GotoTag','D');
        
    case 'NONE'
        handles.sig4param = '0';
        set_param('RadioSYS/From6','GotoTag','E');
        set_param('RadioSYS/From7','GotoTag','E');
end
guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function sig4PM_CreateFcn(hObject, eventdata, handles)
% hObject    handle to sig4PM (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in sig1paramB.
function sig1paramB_Callback(hObject, eventdata, handles)
% hObject    handle to sig1paramB (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
if handles.sig1param == '0'
else
   run(handles.sig1param);
end


% --- Executes on button press in sig2paramB.
function sig2paramB_Callback(hObject, eventdata, handles)
% hObject    handle to sig2paramB (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
if handles.sig2param == '0'
else
   run(handles.sig2param);
end

% --- Executes on button press in sig3paramB.
function sig3paramB_Callback(hObject, eventdata, handles)
% hObject    handle to sig3paramB (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
if handles.sig3param == '0'
else
   run(handles.sig3param);
end

% --- Executes on button press in sig4paramB.
function sig4paramB_Callback(hObject, eventdata, handles)
% hObject    handle to sig4paramB (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
if handles.sig4param == '0'
else
   run(handles.sig4param);
end
