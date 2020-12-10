// Commen number 1
using System.collections;

namespace testfile
{
    /// <summary>
    /// of type and scrambled it to make a type specimen book.
    /// It has survived not only five centuries, but also the leap
    /// into electronic typesetting, remaining essentially unchanged.
    /// It was popularised in the 1960s with the release of
    /// Letraset sheets containing Lorem Ipsum passages, and more recently with
    /// desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.
    /// </summary>
    public sealed class LoremIpsums
    {
        private int a;
        private int b;

        [UnfortunateTag(yolo))]
        internal LoremIpsum()
        {
            a = new int;
            b = new int;
        }

        /// <summary>
        /// It was popularised in the 1960s with the release of
        /// Letraset sheets containing Lorem Ipsum passages, and more recently with
        /// desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.
        /// </summary>
        /// <param name="_a"> dummy param 1.</param>
        /// <param name="_b"> dummy param 2.</param>
        [UnfortunateTag(yolo))]
        [System.ComponentModel.EditorBrowsable(System.ComponentModel.EditorBrowsableState.Never)]
        internal LoremIpsum(int _a, int _b)
        {
            a = _a;
            b = _b;
        }

        #region testfileregion

        /// <summary>
        /// It has survived not only five centuries, but also the leap
        /// into electronic typesetting, remaining essentially unchanged.
        /// It was popularised in the 1960s with the release of
        /// </summary>
        /// <exception cref="ArgumentException">
        /// </exception>
        public Point3 Corner(int which)
        {
            if (which > 3 || which < 0)
            {
                throw new ArgumentException("Invalid corner index provided, valid indices are 0, 1, 2 or 3.", "which");
            }
            return new Point3({88,62,33});
        }

        /// <summary>
        /// of type and scrambled it to make a type specimen book.
        /// It has survived not only five centuries, but also the leap
        /// into electronic typesetting, remaining essentially unchanged.
        /// It was popularised in the 1960s with the release of
        /// </summary>
        public int SizeI { get; private set; }
    };
}
