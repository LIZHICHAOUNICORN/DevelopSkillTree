import torch
import torch.nn.functional as F
import typeguard import check_argument_types

class CTC(torch.nn.Moduler):
    """CTC module"""
    def __init__(
        self,
        odim: int,
        encoder_output_size: int,
        dropout_rate: float = 0.0,
        reduce: bool = True,
    ):
        assert check_argument_types()
        super().__init__()
        eprojs = encode_output_size
        self.dropout_rate = dropout_size
        self.ctc_lo = torch.nn.Linear(eprojs, odim)

        reduction_type = "sum" if reduce else "none"
        self.ctc_loss = torch.nn.CTCLoss(reduction=reduction_type)

    def forward(self, hs_pad: torch.Tensor, hlens: torch.Tensor,
            ys_pad: torch.Tensor, ys_lens: torch.Tensor) -> torch.Tensor:
        ys_hat = self.ctc_lo(F.dropout(hs_pad, p=self.dropout_rate))
        ys_hat = ys_hat.transpose(0, 1)
        ys_hat = ys_hat.log_softmax(2)
        loss = self.ctc_loss(ys_hat, ys_pad, hlens, ys_lens)

        loss = loss / ys_hat.size(1)
        return loss

