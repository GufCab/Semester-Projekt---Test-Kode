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
    public class CpSwitchPower
    {
       private Hashtable UnspecifiedTable = Hashtable.Synchronized(new Hashtable());
       internal UPnPService _S;

       public UPnPService GetUPnPService()
       {
            return(_S);
       }
       public static string SERVICE_NAME = "urn:schemas-upnp-org:service:SwitchPower:";
       public double VERSION
       {
           get
           {
               return(double.Parse(_S.Version));
           }
       }

       public delegate void StateVariableModifiedHandler_Status(CpSwitchPower sender, System.Boolean NewValue);
       private WeakEvent OnStateVariable_Status_Event = new WeakEvent();
       public event StateVariableModifiedHandler_Status OnStateVariable_Status
       {
			add{OnStateVariable_Status_Event.Register(value);}
			remove{OnStateVariable_Status_Event.UnRegister(value);}
       }
       protected void Status_ModifiedSink(UPnPStateVariable Var, object NewValue)
       {
            OnStateVariable_Status_Event.Fire(this, Status);
       }
       public delegate void SubscribeHandler(CpSwitchPower sender, bool Success);
       public event SubscribeHandler OnSubscribe;
       public delegate void Delegate_OnResult_GetStatus(CpSwitchPower sender, System.Boolean ResultStatus, UPnPInvokeException e, object _Tag);
       private WeakEvent OnResult_GetStatus_Event = new WeakEvent();
       public event Delegate_OnResult_GetStatus OnResult_GetStatus
       {
			add{OnResult_GetStatus_Event.Register(value);}
			remove{OnResult_GetStatus_Event.UnRegister(value);}
       }
       public delegate void Delegate_OnResult_GetTarget(CpSwitchPower sender, System.Boolean newTargetValue, UPnPInvokeException e, object _Tag);
       private WeakEvent OnResult_GetTarget_Event = new WeakEvent();
       public event Delegate_OnResult_GetTarget OnResult_GetTarget
       {
			add{OnResult_GetTarget_Event.Register(value);}
			remove{OnResult_GetTarget_Event.UnRegister(value);}
       }
       public delegate void Delegate_OnResult_SetTarget(CpSwitchPower sender, System.Boolean newTargetValue, UPnPInvokeException e, object _Tag);
       private WeakEvent OnResult_SetTarget_Event = new WeakEvent();
       public event Delegate_OnResult_SetTarget OnResult_SetTarget
       {
			add{OnResult_SetTarget_Event.Register(value);}
			remove{OnResult_SetTarget_Event.UnRegister(value);}
       }

        public CpSwitchPower(UPnPService s)
        {
            _S = s;
            _S.OnSubscribe += new UPnPService.UPnPEventSubscribeHandler(_subscribe_sink);
            if (HasStateVariable_Status) _S.GetStateVariableObject("Status").OnModified += new UPnPStateVariable.ModifiedHandler(Status_ModifiedSink);
        }
        public void Dispose()
        {
            _S.OnSubscribe -= new UPnPService.UPnPEventSubscribeHandler(_subscribe_sink);
            OnSubscribe = null;
            if (HasStateVariable_Status) _S.GetStateVariableObject("Status").OnModified -= new UPnPStateVariable.ModifiedHandler(Status_ModifiedSink);
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
        public System.Boolean Status
        {
            get
            {
               return((System.Boolean)_S.GetStateVariable("Status"));
            }
        }
        public System.Boolean Target
        {
            get
            {
               return((System.Boolean)_S.GetStateVariable("Target"));
            }
        }
        public bool HasStateVariable_Status
        {
            get
            {
               if (_S.GetStateVariableObject("Status")==null)
               {
                   return(false);
               }
               else
               {
                   return(true);
               }
            }
        }
        public bool HasStateVariable_Target
        {
            get
            {
               if (_S.GetStateVariableObject("Target")==null)
               {
                   return(false);
               }
               else
               {
                   return(true);
               }
            }
        }
        public bool HasAction_GetStatus
        {
            get
            {
               if (_S.GetAction("GetStatus")==null)
               {
                   return(false);
               }
               else
               {
                   return(true);
               }
            }
        }
        public bool HasAction_GetTarget
        {
            get
            {
               if (_S.GetAction("GetTarget")==null)
               {
                   return(false);
               }
               else
               {
                   return(true);
               }
            }
        }
        public bool HasAction_SetTarget
        {
            get
            {
               if (_S.GetAction("SetTarget")==null)
               {
                   return(false);
               }
               else
               {
                   return(true);
               }
            }
        }
        public void Sync_GetStatus(out System.Boolean ResultStatus)
        {
           UPnPArgument[] args = new UPnPArgument[1];
           args[0] = new UPnPArgument("ResultStatus", "");
            _S.InvokeSync("GetStatus", args);
            ResultStatus = (System.Boolean) args[0].DataValue;
            return;
        }
        public void GetStatus()
        {
            GetStatus(null, null);
        }
        public void GetStatus(object _Tag, Delegate_OnResult_GetStatus _Callback)
        {
           UPnPArgument[] args = new UPnPArgument[1];
           args[0] = new UPnPArgument("ResultStatus", "");
           _S.InvokeAsync("GetStatus", args, new object[2]{_Tag,_Callback}, new UPnPService.UPnPServiceInvokeHandler(Sink_GetStatus), new UPnPService.UPnPServiceInvokeErrorHandler(Error_Sink_GetStatus));
        }
        private void Sink_GetStatus(UPnPService sender, string MethodName, UPnPArgument[] Args, object RetVal, object _Tag)
        {
            object[] StateInfo = (object[])_Tag;
            if (StateInfo[1]!=null)
            {
                ((Delegate_OnResult_GetStatus)StateInfo[1])(this, (System.Boolean )Args[0].DataValue, null, StateInfo[0]);
            }
            else
            {
                OnResult_GetStatus_Event.Fire(this, (System.Boolean )Args[0].DataValue, null, StateInfo[0]);
            }
        }
        private void Error_Sink_GetStatus(UPnPService sender, string MethodName, UPnPArgument[] Args, UPnPInvokeException e, object _Tag)
        {
            object[] StateInfo = (object[])_Tag;
            if (StateInfo[1]!=null)
            {
                ((Delegate_OnResult_GetStatus)StateInfo[1])(this, (System.Boolean)UPnPService.CreateObjectInstance(typeof(System.Boolean),null), e, StateInfo[0]);
            }
            else
            {
                OnResult_GetStatus_Event.Fire(this, (System.Boolean)UPnPService.CreateObjectInstance(typeof(System.Boolean),null), e, StateInfo[0]);
            }
        }
        public void Sync_GetTarget(out System.Boolean newTargetValue)
        {
           UPnPArgument[] args = new UPnPArgument[1];
           args[0] = new UPnPArgument("newTargetValue", "");
            _S.InvokeSync("GetTarget", args);
            newTargetValue = (System.Boolean) args[0].DataValue;
            return;
        }
        public void GetTarget()
        {
            GetTarget(null, null);
        }
        public void GetTarget(object _Tag, Delegate_OnResult_GetTarget _Callback)
        {
           UPnPArgument[] args = new UPnPArgument[1];
           args[0] = new UPnPArgument("newTargetValue", "");
           _S.InvokeAsync("GetTarget", args, new object[2]{_Tag,_Callback}, new UPnPService.UPnPServiceInvokeHandler(Sink_GetTarget), new UPnPService.UPnPServiceInvokeErrorHandler(Error_Sink_GetTarget));
        }
        private void Sink_GetTarget(UPnPService sender, string MethodName, UPnPArgument[] Args, object RetVal, object _Tag)
        {
            object[] StateInfo = (object[])_Tag;
            if (StateInfo[1]!=null)
            {
                ((Delegate_OnResult_GetTarget)StateInfo[1])(this, (System.Boolean )Args[0].DataValue, null, StateInfo[0]);
            }
            else
            {
                OnResult_GetTarget_Event.Fire(this, (System.Boolean )Args[0].DataValue, null, StateInfo[0]);
            }
        }
        private void Error_Sink_GetTarget(UPnPService sender, string MethodName, UPnPArgument[] Args, UPnPInvokeException e, object _Tag)
        {
            object[] StateInfo = (object[])_Tag;
            if (StateInfo[1]!=null)
            {
                ((Delegate_OnResult_GetTarget)StateInfo[1])(this, (System.Boolean)UPnPService.CreateObjectInstance(typeof(System.Boolean),null), e, StateInfo[0]);
            }
            else
            {
                OnResult_GetTarget_Event.Fire(this, (System.Boolean)UPnPService.CreateObjectInstance(typeof(System.Boolean),null), e, StateInfo[0]);
            }
        }
        public void Sync_SetTarget(System.Boolean newTargetValue)
        {
           UPnPArgument[] args = new UPnPArgument[1];
           args[0] = new UPnPArgument("newTargetValue", newTargetValue);
            _S.InvokeSync("SetTarget", args);
            newTargetValue = (System.Boolean) args[0].DataValue;
            return;
        }
        public void SetTarget(System.Boolean newTargetValue)
        {
            SetTarget(newTargetValue, null, null);
        }
        public void SetTarget(System.Boolean newTargetValue, object _Tag, Delegate_OnResult_SetTarget _Callback)
        {
           UPnPArgument[] args = new UPnPArgument[1];
           args[0] = new UPnPArgument("newTargetValue", newTargetValue);
           _S.InvokeAsync("SetTarget", args, new object[2]{_Tag,_Callback}, new UPnPService.UPnPServiceInvokeHandler(Sink_SetTarget), new UPnPService.UPnPServiceInvokeErrorHandler(Error_Sink_SetTarget));
        }
        private void Sink_SetTarget(UPnPService sender, string MethodName, UPnPArgument[] Args, object RetVal, object _Tag)
        {
            object[] StateInfo = (object[])_Tag;
            if (StateInfo[1]!=null)
            {
                ((Delegate_OnResult_SetTarget)StateInfo[1])(this, (System.Boolean )Args[0].DataValue, null, StateInfo[0]);
            }
            else
            {
                OnResult_SetTarget_Event.Fire(this, (System.Boolean )Args[0].DataValue, null, StateInfo[0]);
            }
        }
        private void Error_Sink_SetTarget(UPnPService sender, string MethodName, UPnPArgument[] Args, UPnPInvokeException e, object _Tag)
        {
            object[] StateInfo = (object[])_Tag;
            if (StateInfo[1]!=null)
            {
                ((Delegate_OnResult_SetTarget)StateInfo[1])(this, (System.Boolean )Args[0].DataValue, e, StateInfo[0]);
            }
            else
            {
                OnResult_SetTarget_Event.Fire(this, (System.Boolean )Args[0].DataValue, e, StateInfo[0]);
            }
        }
    }
}