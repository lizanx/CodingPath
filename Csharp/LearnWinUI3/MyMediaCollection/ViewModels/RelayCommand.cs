using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace MyMediaCollection.ViewModels
{
    public class RelayCommand : ICommand
    {
        private readonly Action action;
        private readonly Func<bool> canExecute;

        public RelayCommand(Action action, Func<bool> canExecute)
        {
            if (action is null) throw new ArgumentNullException(nameof(action));

            this.action = action;
            this.canExecute = canExecute;
        }

        public RelayCommand(Action action) : this(action, null) { }

        public bool CanExecute(object parameter) => canExecute is null || canExecute();

        public void Execute(object parameter) => action();

        public event EventHandler CanExecuteChanged;

        public void RaiseCanExecuteChanged() =>
            CanExecuteChanged?.Invoke(this, EventArgs.Empty);
    }
}
