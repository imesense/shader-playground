using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Runtime.CompilerServices;

using Avalonia.Controls;
using Avalonia.Input;
using Avalonia.Interactivity;
using Avalonia.Media;

using AvaloniaEdit;
using AvaloniaEdit.CodeCompletion;
using AvaloniaEdit.Document;
using AvaloniaEdit.Editing;
using AvaloniaEdit.Folding;
using AvaloniaEdit.Indentation.CSharp;
using AvaloniaEdit.Rendering;
using AvaloniaEdit.TextMate;

using ImeSense.ShaderPlayground.Interop;

using TextMateSharp.Grammars;

namespace ImeSense.ShaderPlayground.Views;

public partial class MainWindow : Window {
    private readonly TextEditor _textEditor;
    private FoldingManager _foldingManager = null!;
    private readonly TextMate.Installation _textMateInstallation;
    private CompletionWindow _completionWindow = null!;
    private OverloadInsightWindow _insightWindow = null!;
    private Button _changeThemeButton;
    private ComboBox _syntaxModeCombo;
    private TextBlock _statusTextBlock;
    private ElementGenerator _generator = new();
    private RegistryOptions _registryOptions;
    private int _currentTheme = (int) ThemeName.DarkPlus;

    public MainWindow() {
        InitializeComponent();

        var viewport = new Viewport();
        viewportContentControl.Content = viewport;

        _textEditor = this.FindControl<TextEditor>("Editor")!;
        _textEditor.HorizontalScrollBarVisibility = Avalonia.Controls.Primitives.ScrollBarVisibility.Visible;
        _textEditor.Background = Brushes.Transparent;
        _textEditor.ShowLineNumbers = true;

        _textEditor.ContextMenu = new ContextMenu {
            ItemsSource = new List<MenuItem> {
                new() {
                    Header = "Copy",
                    InputGesture = new KeyGesture(Key.C, KeyModifiers.Control),
                },
                new() {
                    Header = "Paste",
                    InputGesture = new KeyGesture(Key.V, KeyModifiers.Control),
                },
                new() {
                    Header = "Cut",
                    InputGesture = new KeyGesture(Key.X, KeyModifiers.Control),
                }
            },
        };

        _textEditor.TextArea.Background = Background;

        _textEditor.TextArea.TextEntered += (o, e) => {
            if (e.Text == ".") {
                _completionWindow = new CompletionWindow(_textEditor.TextArea);
                _completionWindow.Closed += (o, args) => _completionWindow = null!;

                var data = _completionWindow.CompletionList.CompletionData;
                data.Add(new MyCompletionData("Item1"));
                data.Add(new MyCompletionData("Item2"));
                data.Add(new MyCompletionData("Item3"));
                data.Add(new MyCompletionData("Item4"));
                data.Add(new MyCompletionData("Item5"));
                data.Add(new MyCompletionData("Item6"));
                data.Add(new MyCompletionData("Item7"));
                data.Add(new MyCompletionData("Item8"));
                data.Add(new MyCompletionData("Item9"));
                data.Add(new MyCompletionData("Item10"));
                data.Add(new MyCompletionData("Item11"));
                data.Add(new MyCompletionData("Item12"));
                data.Add(new MyCompletionData("Item13"));

                _completionWindow.Show();
            } else if (e.Text == "(") {
                _insightWindow = new OverloadInsightWindow(_textEditor.TextArea);
                _insightWindow.Closed += (o, args) => _insightWindow = null!;

                _insightWindow.Provider = new MyOverloadProvider(new[] {
                    ("Method1(int, string)", "Method1 description"),
                    ("Method2(int)", "Method2 description"),
                    ("Method3(string)", "Method3 description"),
                });

                _insightWindow.Show();
            }
        };

        _textEditor.TextArea.TextEntering += (o, e) => {
            if (e?.Text?.Length > 0 && _completionWindow != null) {
                if (!char.IsLetterOrDigit(e.Text[0])) {
                    _completionWindow.CompletionList.RequestInsertion(e);
                }
            }

            _insightWindow?.Hide();
        };

        _textEditor.Options.ShowBoxForControlCharacters = true;
        _textEditor.Options.ColumnRulerPositions = new List<int>() { 80, 100 };
        _textEditor.TextArea.IndentationStrategy = new CSharpIndentationStrategy(_textEditor.Options);

        _textEditor.TextArea.Caret.PositionChanged += (o, e) => {
            if (_statusTextBlock is not null) {
                _statusTextBlock.Text = string.Format("Line {0} Column {1}",
                    _textEditor.TextArea.Caret.Line, _textEditor.TextArea.Caret.Column);
            }
        };

        _textEditor.TextArea.RightClickMovesCaret = true;

        //_addControlButton = this.FindControl<Button>("addControlBtn");
        // _addControlButton.Click += AddControlButton_Click;

        //_clearControlButton = this.FindControl<Button>("clearControlBtn");
        //_clearControlButton.Click += ClearControlButton_Click;

        _changeThemeButton = this.FindControl<Button>("changeThemeBtn")!;
        _changeThemeButton.Click += (o, e) => {
            _currentTheme = (_currentTheme + 1) % Enum.GetNames(typeof(ThemeName)).Length;

            _textMateInstallation?.SetTheme(_registryOptions?.LoadTheme((ThemeName) _currentTheme));
        };

        _textEditor.TextArea.TextView.ElementGenerators.Add(_generator);

        _registryOptions = new RegistryOptions((ThemeName) _currentTheme);

        _textMateInstallation = _textEditor.InstallTextMate(_registryOptions);

        Language hlslLanguage = _registryOptions.GetLanguageByExtension(".hlsl");

        _syntaxModeCombo = this.FindControl<ComboBox>("syntaxModeCombo")!;
        _syntaxModeCombo.ItemsSource = new List<Language> {
            hlslLanguage,
        };
        _syntaxModeCombo.SelectedItem = hlslLanguage;
        _syntaxModeCombo.SelectionChanged += (o, e) => {
            RemoveUnderlineAndStrikethroughTransformer();

            Language language = (Language) _syntaxModeCombo.SelectedItem!;

            if (_foldingManager != null) {
                _foldingManager.Clear();
                FoldingManager.Uninstall(_foldingManager);
            }

            string scopeName = _registryOptions.GetScopeByLanguageId(language.Id);

            _textMateInstallation.SetGrammar(null);
            _textEditor.Document = new TextDocument(ResourceLoader.LoadSampleFile(scopeName));
            _textMateInstallation.SetGrammar(scopeName);

            if (language.Id == "xml") {
                _foldingManager = FoldingManager.Install(_textEditor.TextArea);

                var strategy = new XmlFoldingStrategy();
                strategy.UpdateFoldings(_foldingManager, _textEditor.Document);
                return;
            }
        };

        string scopeName = _registryOptions.GetScopeByLanguageId(hlslLanguage.Id);

        _textEditor.Document = new TextDocument(
            "// AvaloniaEdit supports displaying control chars: \a or \b or \v" + Environment.NewLine +
            "// AvaloniaEdit supports displaying underline and strikethrough" + Environment.NewLine +
            ResourceLoader.LoadSampleFile(scopeName));
        _textMateInstallation.SetGrammar(_registryOptions.GetScopeByLanguageId(hlslLanguage.Id));
        _textEditor.TextArea.TextView.LineTransformers.Add(new UnderlineAndStrikeThroughTransformer());

        _statusTextBlock = this.Find<TextBlock>("StatusText")!;

        AddHandler(PointerWheelChangedEvent, (o, i) => {
            if (i.KeyModifiers != KeyModifiers.Control) return;
            if (i.Delta.Y > 0) _textEditor.FontSize++;
            else _textEditor.FontSize = _textEditor.FontSize > 1 ? _textEditor.FontSize - 1 : 1;
        }, RoutingStrategies.Bubble, true);
    }

    private void RemoveUnderlineAndStrikethroughTransformer() {
        for (int i = _textEditor.TextArea.TextView.LineTransformers.Count - 1; i >= 0; i--) {
            if (_textEditor.TextArea.TextView.LineTransformers[i] is UnderlineAndStrikeThroughTransformer) {
                _textEditor.TextArea.TextView.LineTransformers.RemoveAt(i);
            }
        }
    }

    private void AddControlButton_Click(object sender, RoutedEventArgs e) {
        _generator.controls.Add(new KeyValuePair<int, Control>(_textEditor.CaretOffset, new Button() { Content = "Click me", Cursor = Cursor.Default }));
        _textEditor.TextArea.TextView.Redraw();
    }

    private void ClearControlButton_Click(object sender, RoutedEventArgs e) {
        //TODO: delete elements using back key
        _generator.controls.Clear();
        _textEditor.TextArea.TextView.Redraw();
    }

    class UnderlineAndStrikeThroughTransformer : DocumentColorizingTransformer {
        protected override void ColorizeLine(DocumentLine line) {
            if (line.LineNumber == 2) {
                string lineText = CurrentContext.Document.GetText(line);

                int indexOfUnderline = lineText.IndexOf("underline");
                int indexOfStrikeThrough = lineText.IndexOf("strikethrough");

                if (indexOfUnderline != -1) {
                    ChangeLinePart(
                        line.Offset + indexOfUnderline,
                        line.Offset + indexOfUnderline + "underline".Length,
                        visualLine => {
                            if (visualLine.TextRunProperties.TextDecorations != null) {
                                var textDecorations = new TextDecorationCollection(visualLine.TextRunProperties.TextDecorations) {
                                    TextDecorations.Underline[0],
                                };

                                visualLine.TextRunProperties.SetTextDecorations(textDecorations);
                            } else {
                                visualLine.TextRunProperties.SetTextDecorations(TextDecorations.Underline);
                            }
                        }
                    );
                }

                if (indexOfStrikeThrough != -1) {
                    ChangeLinePart(
                        line.Offset + indexOfStrikeThrough,
                        line.Offset + indexOfStrikeThrough + "strikethrough".Length,
                        visualLine => {
                            if (visualLine.TextRunProperties.TextDecorations != null) {
                                var textDecorations = new TextDecorationCollection(visualLine.TextRunProperties.TextDecorations) {
                                    TextDecorations.Strikethrough[0],
                                };

                                visualLine.TextRunProperties.SetTextDecorations(textDecorations);
                            } else {
                                visualLine.TextRunProperties.SetTextDecorations(TextDecorations.Strikethrough);
                            }
                        }
                    );
                }
            }
        }
    }

    private class MyOverloadProvider : IOverloadProvider {
        private readonly IList<(string header, string content)> _items;
        private int _selectedIndex;

        public MyOverloadProvider(IList<(string header, string content)> items) {
            _items = items;
            SelectedIndex = 0;
        }

        public int SelectedIndex {
            get => _selectedIndex;
            set {
                _selectedIndex = value;
                OnPropertyChanged();
                // ReSharper disable ExplicitCallerInfoArgument
                OnPropertyChanged(nameof(CurrentHeader));
                OnPropertyChanged(nameof(CurrentContent));
                // ReSharper restore ExplicitCallerInfoArgument
            }
        }

        public int Count => _items.Count;
        public string CurrentIndexText => $"{SelectedIndex + 1} of {Count}";
        public object CurrentHeader => _items[SelectedIndex].header;
        public object CurrentContent => _items[SelectedIndex].content;

        public event PropertyChangedEventHandler? PropertyChanged;

        private void OnPropertyChanged([CallerMemberName] string propertyName = null!) {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }

    public class MyCompletionData : ICompletionData {
        public MyCompletionData(string text) {
            Text = text;
        }

        public IImage Image => null!;

        public string Text { get; }

        public object Content => Text;

        public object Description => "Description for " + Text;

        public double Priority { get; } = 0;

        public void Complete(TextArea textArea, ISegment completionSegment,
            EventArgs insertionRequestEventArgs) {
            textArea.Document.Replace(completionSegment, Text);
        }
    }

    class ElementGenerator : VisualLineElementGenerator, IComparer<KeyValuePair<int, Control>> {
        public List<KeyValuePair<int, Control>> controls = new();

        public override int GetFirstInterestedOffset(int startOffset) {
            int pos = controls.BinarySearch(new KeyValuePair<int, Control>(startOffset, null!), this);
            if (pos < 0)
                pos = ~pos;
            if (pos < controls.Count)
                return controls[pos].Key;
            else
                return -1;
        }

        public override VisualLineElement ConstructElement(int offset) {
            int pos = controls.BinarySearch(new KeyValuePair<int, Control>(offset, null!), this);
            if (pos >= 0)
                return new InlineObjectElement(0, controls[pos].Value);
            else
                return null!;
        }

        int IComparer<KeyValuePair<int, Control>>.Compare(KeyValuePair<int, Control> x, KeyValuePair<int, Control> y) {
            return x.Key.CompareTo(y.Key);
        }
    }
}
