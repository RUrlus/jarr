import importlib
import importlib.metadata

__version__ = importlib.metadata.version("jarr")
from jarr.lib import _jarr_ext as ext

__all__ = ["ext", "__version__"]
