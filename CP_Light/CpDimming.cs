using System;
using System.Collections;
using System.Threading;
using OpenSource.Utilities;
using OpenSource.UPnP;

namespace OpenSource.DeviceBuilder
{
    /// <summary>
    /// Transparent ClientSide UPnP Service
    /// </summary>
    public class CpDimming
    {
       private Hashtable UnspecifiedTable = Hashtable.Synchronized(new Hashtable());
       internal UPnPService _S;

       public UPnPService GetUPnPService()
       {
            return(_S);
       }
       public static string SERVICE_NAME = "urn:schemas-upnp-org:service:Dimming:";
       public double VERSION
       {
           get
           {
               return(double.Parse(_S.Version));
           }
       }

       public delegate void StateVariableModifiedHandler_LoadLevelStatus(CpDimming sender, System.Byte NewValue);
       private WeakEvent OnStateVariable_LoadLevelStatus_Event = new WeakEvent();
       public event StateVariableModifiedHandler_LoadLevelStatus OnStateVariable_LoadLevelStatus
       {
			add{OnStateVariable_LoadLevelStatus_Event.Register(value);}
			remove{OnStateVariable_LoadLevelStatus_Event.UnRegister(value);}
       }
       protected void LoadLevelStatus_ModifiedSink(UPnPStateVariable Var, object NewValue)
       {
            OnStateVariable_LoadLevelStatus_Event.Fire(this, LoadLevelStatus);
       }
       public delegate void SubscribeHandler(CpDimming sender, bool Success);
       public event SubscribeHandler OnSubscribe;
       public delegate void Delegate_OnResult_GetLoadLevelStatus(CpDimming sender, System.Byte RetLoadLevelStatus, UPnPInvokeException e, object _Tag);
       private WeakEvent OnResult_GetLoadLevelStatus_Event = new WeakEvent();
       public event Delegate_OnResult_GetLoadLevelStatus OnResult_GetLoadLevelStatus
       {
			add{OnResult_GetLoadLevelStatus_Event.Register(value);}
			remove{OnResult_GetLoadLevelStatus_Event.UnRegister(value);}
       }
       public delegate void Delegate_OnResult_GetLoadLevelTarget(CpDimming sender, System.Byte NewLoadLevelTarget, UPnPInvokeException e, object _Tag);
       private WeakEvent OnResult_GetLoadLevelTarget_Event = new WeakEvent();
       public event Delegate_OnResult_GetLoadLevelTarget OnResult_GetLoadLevelTarget
       {
			add{OnResult_GetLoadLevelTarget_Event.Register(value);}
			remove{OnResult_GetLoadLevelTarget_Event.UnRegister(value);}
       }
       public delegate void Delegate_OnResult_GetMinLevel(CpDimming sender, System.Byte MinLevel, UPnPInvokeException e, object _Tag);
       private WeakEvent OnResult_GetMinLevel_Event = new WeakEvent();
       public event Delegate_OnResult_GetMinLevel OnResult_GetMinLevel
       {
			add{OnResult_GetMinLevel_Event.Register(value);}
			remove{OnResult_GetMinLevel_Event.UnRegister(value);}
       }
       public delegate void Delegate_OnResult_SetLoadLevelTarget(CpDimming sender, System.Byte NewLoadLevelTarget, UPnPInvokeException e, object _Tag);
       private WeakEvent OnResult_SetLoadLevelTarget_Event = new WeakEvent();
       public event Delegate_OnResult_SetLoadLevelTarget OnResult_SetLoadLevelTarget
       {
			add{OnResult_SetLoadLevelTarget_Event.Register(value);}
			remove{OnResult_SetLoadLevelTarget_Event.UnRegister(value);}
       }

        public CpDimming(UPnPService s)
        {
            _S = s;
            _S.OnSubscribe += new UPnPService.UPnPEventSubscribeHandler(_subscribe_sink);
            if (HasStateVariable_LoadLevelStatus) _S.GetStateVariableObject("LoadLevelStatus").OnModified += new UPnPStateVariable.ModifiedHandler(LoadLevelStatus_ModifiedSink);
        }
        public void Dispose()
        {
            _S.OnSubscribe -= new UPnPService.UPnPEventSubscribeHandler(_subscribe_sink);
            OnSubscribe = null;
            if (HasStateVariable_LoadLevelStatus) _S.GetStateVariableObject("LoadLevelStatus").OnModified -= new UPnPStateVariable.ModifiedHandler(LoadLevelStatus_ModifiedSink);
        }
        public void _subscribe(int Timeout)
        {
            _S.Subscribe(Timeout, null);
        }
        protected void _subscribe_sink(UPnPService sender, bool OK)
        {
            if (OnSubscribe!=null)
            {
                OnSubscribe(this, OK);
            }
        }
        public void SetUnspecifiedValue(string EnumType, string val)
        {
            string hash = Thread.CurrentThread.GetHashCode().ToString() + ":" + EnumType;
            UnspecifiedTable[hash] = val;
        }
        public string GetUnspecifiedValue(string EnumType)
        {
            string hash = Thread.CurrentThread.GetHashCode().ToString() + ":" + EnumType;
            if (UnspecifiedTable.ContainsKey(hash)==false)
            {
               return("");
            }
            string RetVal = (string)UnspecifiedTable[hash];
            return(RetVal);
        }
        public System.Byte LoadLevelStatus
        {
            get
            {
               return((System.Byte)_S.GetStateVariable("LoadLevelStatus"));
            }
        }
        public System.Byte MinLevel
        {
            get
            {
               return((System.Byte)_S.GetStateVariable("MinLevel"));
            }
        }
        public System.Byte LoadLevelTarget
        {
            get
            {
               return((System.Byte)_S.GetStateVariable("LoadLevelTarget"));
            }
        }
        public bool HasMaximum_LoadLevelStatus
        {
             get
             {
                 return(_S.GetStateVariableObject("LoadLevelStatus").Maximum!=null);
             }
        }
        public bool HasMinimum_LoadLevelStatus
        {
             get
             {
                 return(_S.GetStateVariableObject("LoadLevelStatus").Minimum!=null);
             }
        }
        public System.Byte Maximum_LoadLevelStatus
        {
             get
             {
                 return((System.Byte)_S.GetStateVariableObject("LoadLevelStatus").Maximum);
             }
        }
        public System.Byte Minimum_LoadLevelStatus
        {
             get
             {
                 return((System.Byte)_S.GetStateVariableObject("LoadLevelStatus").Minimum);
             }
        }
        public bool HasStateVariable_LoadLevelStatus
        {
            get
            {
               if (_S.GetStateVariableObject("LoadLevelStatus")==null)
               {
                   return(false);
               }
               else
               {
                   return(true);
               }
            }
        }
        public bool HasStateVariable_MinLevel
        {
            get
            {
               if (_S.GetStateVariableObject("MinLevel")==null)
               {
                   return(false);
               }
               else
               {
                   return(true);
               }
            }
        }
        public bool HasMaximum_LoadLevelTarget
        {
             get
             {
                 return(_S.GetStateVariableObject("LoadLevelTarget").Maximum!=null);
             }
        }
        public bool HasMinimum_LoadLevelTarget
        {
             get
             {
                 return(_S.GetStateVariableObject("LoadLevelTarget").Minimum!=null);
             }
        }
        public System.Byte Maximum_LoadLevelTarget
        {
             get
             {
                 return((System.Byte)_S.GetStateVariableObject("LoadLevelTarget").Maximum);
             }
        }
        public System.Byte Minimum_LoadLevelTarget
        {
             get
             {
                 return((System.Byte)_S.GetStateVariableObject("LoadLevelTarget").Minimum);
             }
        }
        public bool HasStateVariable_LoadLevelTarget
        {
            get
            {
               if (_S.GetStateVariableObject("LoadLevelTarget")==null)
               {
                   return(false);
               }
               else
               {
                   return(true);
               }
            }
        }
        public bool HasAction_GetLoadLevelStatus
        {
            get
            {
               if (_S.GetAction("GetLoadLevelStatus")==null)
               {
                   return(false);
               }
               else
               {
                   return(true);
               }
            }
        }
        public bool HasAction_GetLoadLevelTarget
        {
            get
            {
               if (_S.GetAction("GetLoadLevelTarget")==null)
               {
                   return(false);
               }
               else
               {
                   return(true);
               }
            }
        }
        public bool HasAction_GetMinLevel
        {
            get
            {
               if (_S.GetAction("GetMinLevel")==null)
               {
                   return(false);
               }
               else
               {
                   return(true);
               }
            }
        }
        public bool HasAction_SetLoadLevelTarget
        {
            get
            {
               if (_S.GetAction("SetLoadLevelTarget")==null)
               {
                   return(false);
               }
               else
               {
                   return(true);
               }
            }
        }
        public void Sync_GetLoadLevelStatus(out System.Byte RetLoadLevelStatus)
        {
           UPnPArgument[] args = new UPnPArgument[1];
           args[0] = new UPnPArgument("RetLoadLevelStatus", "");
            _S.InvokeSync("GetLoadLevelStatus", args);
            RetLoadLevelStatus = (System.Byte) args[0].DataValue;
            return;
        }
        public void GetLoadLevelStatus()
        {
            GetLoadLevelStatus(null, null);
        }
        public void GetLoadLevelStatus(object _Tag, Delegate_OnResult_GetLoadLevelStatus _Callback)
        {
           UPnPArgument[] args = new UPnPArgument[1];
           args[0] = new UPnPArgument("RetLoadLevelStatus", "");
           _S.InvokeAsync("GetLoadLevelStatus", args, new object[2]{_Tag,_Callback}, new UPnPService.UPnPServiceInvokeHandler(Sink_GetLoadLevelStatus), new UPnPService.UPnPServiceInvokeErrorHandler(Error_Sink_GetLoadLevelStatus));
        }
        private void Sink_GetLoadLevelStatus(UPnPService sender, string MethodName, UPnPArgument[] Args, object RetVal, object _Tag)
        {
            object[] StateInfo = (object[])_Tag;
            if (StateInfo[1]!=null)
            {
                ((Delegate_OnResult_GetLoadLevelStatus)StateInfo[1])(this, (System.Byte )Args[0].DataValue, null, StateInfo[0]);
            }
            else
            {
                OnResult_GetLoadLevelStatus_Event.Fire(this, (System.Byte )Args[0].DataValue, null, StateInfo[0]);
            }
        }
        private void Error_Sink_GetLoadLevelStatus(UPnPService sender, string MethodName, UPnPArgument[] Args, UPnPInvokeException e, object _Tag)
        {
            object[] StateInfo = (object[])_Tag;
            if (StateInfo[1]!=null)
            {
                ((Delegate_OnResult_GetLoadLevelStatus)StateInfo[1])(this, (System.Byte)UPnPService.CreateObjectInstance(typeof(System.Byte),null), e, StateInfo[0]);
            }
            else
            {
                OnResult_GetLoadLevelStatus_Event.Fire(this, (System.Byte)UPnPService.CreateObjectInstance(typeof(System.Byte),null), e, StateInfo[0]);
            }
        }
        public void Sync_GetLoadLevelTarget(out System.Byte NewLoadLevelTarget)
        {
           UPnPArgument[] args = new UPnPArgument[1];
           args[0] = new UPnPArgument("NewLoadLevelTarget", "");
            _S.InvokeSync("GetLoadLevelTarget", args);
            NewLoadLevelTarget = (System.Byte) args[0].DataValue;
            return;
        }
        public void GetLoadLevelTarget()
        {
            GetLoadLevelTarget(null, null);
        }
        public void GetLoadLevelTarget(object _Tag, Delegate_OnResult_GetLoadLevelTarget _Callback)
        {
           UPnPArgument[] args = new UPnPArgument[1];
           args[0] = new UPnPArgument("NewLoadLevelTarget", "");
           _S.InvokeAsync("GetLoadLevelTarget", args, new object[2]{_Tag,_Callback}, new UPnPService.UPnPServiceInvokeHandler(Sink_GetLoadLevelTarget), new UPnPService.UPnPServiceInvokeErrorHandler(Error_Sink_GetLoadLevelTarget));
        }
        private void Sink_GetLoadLevelTarget(UPnPService sender, string MethodName, UPnPArgument[] Args, object RetVal, object _Tag)
        {
            object[] StateInfo = (object[])_Tag;
            if (StateInfo[1]!=null)
            {
                ((Delegate_OnResult_GetLoadLevelTarget)StateInfo[1])(this, (System.Byte )Args[0].DataValue, null, StateInfo[0]);
            }
            else
            {
                OnResult_GetLoadLevelTarget_Event.Fire(this, (System.Byte )Args[0].DataValue, null, StateInfo[0]);
            }
        }
        private void Error_Sink_GetLoadLevelTarget(UPnPService sender, string MethodName, UPnPArgument[] Args, UPnPInvokeException e, object _Tag)
        {
            object[] StateInfo = (object[])_Tag;
            if (StateInfo[1]!=null)
            {
                ((Delegate_OnResult_GetLoadLevelTarget)StateInfo[1])(this, (System.Byte)UPnPService.CreateObjectInstance(typeof(System.Byte),null), e, StateInfo[0]);
            }
            else
            {
                OnResult_GetLoadLevelTarget_Event.Fire(this, (System.Byte)UPnPService.CreateObjectInstance(typeof(System.Byte),null), e, StateInfo[0]);
            }
        }
        public void Sync_GetMinLevel(out System.Byte MinLevel)
        {
           UPnPArgument[] args = new UPnPArgument[1];
           args[0] = new UPnPArgument("MinLevel", "");
            _S.InvokeSync("GetMinLevel", args);
            MinLevel = (System.Byte) args[0].DataValue;
            return;
        }
        public void GetMinLevel()
        {
            GetMinLevel(null, null);
        }
        public void GetMinLevel(object _Tag, Delegate_OnResult_GetMinLevel _Callback)
        {
           UPnPArgument[] args = new UPnPArgument[1];
           args[0] = new UPnPArgument("MinLevel", "");
           _S.InvokeAsync("GetMinLevel", args, new object[2]{_Tag,_Callback}, new UPnPService.UPnPServiceInvokeHandler(Sink_GetMinLevel), new UPnPService.UPnPServiceInvokeErrorHandler(Error_Sink_GetMinLevel));
        }
        private void Sink_GetMinLevel(UPnPService sender, string MethodName, UPnPArgument[] Args, object RetVal, object _Tag)
        {
            object[] StateInfo = (object[])_Tag;
            if (StateInfo[1]!=null)
            {
                ((Delegate_OnResult_GetMinLevel)StateInfo[1])(this, (System.Byte )Args[0].DataValue, null, StateInfo[0]);
            }
            else
            {
                OnResult_GetMinLevel_Event.Fire(this, (System.Byte )Args[0].DataValue, null, StateInfo[0]);
            }
        }
        private void Error_Sink_GetMinLevel(UPnPService sender, string MethodName, UPnPArgument[] Args, UPnPInvokeException e, object _Tag)
        {
            object[] StateInfo = (object[])_Tag;
            if (StateInfo[1]!=null)
            {
                ((Delegate_OnResult_GetMinLevel)StateInfo[1])(this, (System.Byte)UPnPService.CreateObjectInstance(typeof(System.Byte),null), e, StateInfo[0]);
            }
            else
            {
                OnResult_GetMinLevel_Event.Fire(this, (System.Byte)UPnPService.CreateObjectInstance(typeof(System.Byte),null), e, StateInfo[0]);
            }
        }
        public void Sync_SetLoadLevelTarget(System.Byte NewLoadLevelTarget)
        {
           UPnPArgument[] args = new UPnPArgument[1];
           args[0] = new UPnPArgument("NewLoadLevelTarget", NewLoadLevelTarget);
            _S.InvokeSync("SetLoadLevelTarget", args);
            NewLoadLevelTarget = (System.Byte) args[0].DataValue;
            return;
        }
        public void SetLoadLevelTarget(System.Byte NewLoadLevelTarget)
        {
            SetLoadLevelTarget(NewLoadLevelTarget, null, null);
        }
        public void SetLoadLevelTarget(System.Byte NewLoadLevelTarget, object _Tag, Delegate_OnResult_SetLoadLevelTarget _Callback)
        {
           UPnPArgument[] args = new UPnPArgument[1];
           args[0] = new UPnPArgument("NewLoadLevelTarget", NewLoadLevelTarget);
           _S.InvokeAsync("SetLoadLevelTarget", args, new object[2]{_Tag,_Callback}, new UPnPService.UPnPServiceInvokeHandler(Sink_SetLoadLevelTarget), new UPnPService.UPnPServiceInvokeErrorHandler(Error_Sink_SetLoadLevelTarget));
        }
        private void Sink_SetLoadLevelTarget(UPnPService sender, string MethodName, UPnPArgument[] Args, object RetVal, object _Tag)
        {
            object[] StateInfo = (object[])_Tag;
            if (StateInfo[1]!=null)
            {
                ((Delegate_OnResult_SetLoadLevelTarget)StateInfo[1])(this, (System.Byte )Args[0].DataValue, null, StateInfo[0]);
            }
            else
            {
                OnResult_SetLoadLevelTarget_Event.Fire(this, (System.Byte )Args[0].DataValue, null, StateInfo[0]);
            }
        }
        private void Error_Sink_SetLoadLevelTarget(UPnPService sender, string MethodName, UPnPArgument[] Args, UPnPInvokeException e, object _Tag)
        {
            object[] StateInfo = (object[])_Tag;
            if (StateInfo[1]!=null)
            {
                ((Delegate_OnResult_SetLoadLevelTarget)StateInfo[1])(this, (System.Byte )Args[0].DataValue, e, StateInfo[0]);
            }
            else
            {
                OnResult_SetLoadLevelTarget_Event.Fire(this, (System.Byte )Args[0].DataValue, e, StateInfo[0]);
            }
        }
    }
}